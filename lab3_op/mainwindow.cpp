#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->selectButton, &QPushButton::clicked, this, &MainWindow::on_selectFileButton_clicked);
    connect(ui->loadDataButton, &QPushButton::clicked, this, &MainWindow::on_loadDataButton_clicked);
    connect(ui->calculateMetricsButton, &QPushButton::clicked, this, &MainWindow::on_calculateMetricsButton_clicked);
    doOperation(Initialization, &context, NULL);
    updateLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectFileButton_clicked() {
    AppParams param;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Выберите CSV файл"), "", tr("CSV файлы (*.csv);;Все файлы (*.*)"));
    std::string stdStr = fileName.toStdString();
    const char* cStr = stdStr.c_str();
    strcpy(param.fileName, cStr);

    doOperation(SetFileName, &context, &param);

    ui->fileNameLabel->setText(context.fileName);
}

void MainWindow::on_loadDataButton_clicked() {
    AppParams param;

    std::string stdStrRegion = ui->regionLineEdit->text().toStdString();
    const char* cStrRegion = stdStrRegion.c_str();
    strcpy(param.region, cStrRegion);

    doOperation(SetRegion,&context,&param);

    doOperation(Loading,&context, NULL);

    updateLabels();
}

void MainWindow::on_calculateMetricsButton_clicked() {
    AppParams param;

    std::string stdStrRegion = ui->regionLineEdit->text().toStdString();
    const char* cStrRegion = stdStrRegion.c_str();
    strcpy(param.region, cStrRegion);

    std::string stdStrColumn = ui->columnNumLineEdit->text().toStdString();
    const char* cStrColumn = stdStrColumn.c_str();
    strcpy(param.column, cStrColumn);

    doOperation(SetRegion, &context, &param);
    doOperation(SetIndex, &context, &param);

    doOperation(Calculation, &context, NULL);
    if (context.errorData == NoErrors) {
        setGraphic();
    }
    updateLabels();
}

void MainWindow::updateLabels() {
    if (context.table != NULL) {
        setTable();
    }
    ui->minLabel->setText(QString::number(context.min));
    ui->maxLabel->setText(QString::number(context.max));
    ui->medianLabel->setText(QString::number(context.median));
    ui->numberOfLinesLabel->setText(QString::number(context.numberOfLines));
    ui->errorLinesLabel->setText(QString::number(context.numberOfErrorLines));
    ui->successLinesLabel->setText(QString::number(context.numberOfSuccessLines));
    errorCodeHandler();
}

void MainWindow::errorCodeHandler() {
    char* errorText = " ";
    switch(context.errorData) {
    case NoErrors:
        errorText = NO_ERRORS;
        break;
    case FileError:
        errorText = FILE_ERROR;
        break;
    case ColumnError:
        errorText = COLUMN_ERROR;
        break;
    case RegionError:
        errorText = REGION_ERROR;
        break;
    case EmptyFileNameError:
        errorText = FILE_NOT_CHOSEN_ERROR;
        break;
    case ZeroRowsError:
        errorText = ZERO_ROWS_ERROR;
        break;
    case EmptyTableError:
        errorText = EMPTY_TABLE_ERROR;
        break;
    case MemoryAllocationError:
        errorText = ALLOCATION_ERROR;
        break;
    }
    ui->errorLabel->setText(errorText);
}

void MainWindow::setTable() {
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(7);

    QStringList headers;
    headers << "Year" << "Region" << "Natural Population Growth" << "Birth Rate" << "Death Rate" << "General Demographic Weight" << "Urbanisation";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    Node* current = context.table->first;
    if (!strcmp(context.region, "")) {
        setFullTable(current);
    } else {
        setRegionTable(current);
    }
}

void MainWindow::setFullTable(Node* current) {
    int row = 0;
    ui->tableWidget->setRowCount(context.numberOfSuccessLines);
    while (current) {
        setRow(current, row);
        current = current->next;
        ++row;
    }
}

void MainWindow::setRegionTable(Node* current) {
    int row = 0;
    while (current) {
        if (!strcmp(current->data.region, context.region)) {
            ui->tableWidget->insertRow(row);
            setRow(current,row);
            ++row;
        }
        current = current->next;
    }
}

void MainWindow::setRow(Node* current,int row) {
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(current->data.year)));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString(current->data.region)));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(current->data.naturalPopulationGrowth)));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(current->data.birthRate)));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(current->data.deathRate)));
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(current->data.generalDemographicWeight)));
    ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(current->data.urbanisation)));
}


double MainWindow::getField(Node* p, int column) {
    double field = 0;
    switch(column) {
    case 3:
        field = p->data.naturalPopulationGrowth;
        break;
    case 4:
        field = p->data.birthRate;
        break;
    case 5:
        field = p->data.deathRate;
        break;
    case 6:
        field = p->data.generalDemographicWeight;
        break;
    case 7:
        field = p->data.urbanisation;
        break;
    }
    return field;
}

void MainWindow::setGraphic() {
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    int cellSize = 40;
    int width = 50*cellSize;
    int height = 55*cellSize;

    scene->setSceneRect(-8*cellSize, -30 *cellSize, width, height);

    drawOY(scene,cellSize);

    drawGraphe(scene,cellSize);
}

void MainWindow::drawOY(QGraphicsScene *scene, int cellSize) {
    QPen yAxisPen(Qt::white);
    int modif = 1;
    int yCounter = 1;
    int yColumnLength = 30;
    double yPointCoordHigher = 25.25;
    double yPointCoordLower = 5;
    if (atoi(context.column) > 5) {
        modif *= 10;
        yCounter*=modif;
        yColumnLength = 10;
        yPointCoordHigher = 5.25;
    }
    if (context.min < 0) {
        yCounter*=-15;
        yPointCoordLower += 15;
    }
    scene->addLine(-5*cellSize, yPointCoordLower*cellSize, -5*cellSize, -yPointCoordHigher * cellSize, yAxisPen);

    for (; yCounter <= yColumnLength*modif; yCounter += modif) {
        QGraphicsEllipseItem *markerY = new QGraphicsEllipseItem(0, 0, 10, 10);
        markerY->setBrush(Qt::white);
        markerY->setPos(-5*cellSize - 5,5*cellSize - yCounter/modif * cellSize);
        scene->addItem(markerY);

        QGraphicsTextItem *textItemY = scene->addText(QString::number(yCounter));
        textItemY->setPos(-5*cellSize - 30,5*cellSize - yCounter/modif * cellSize);
    }

    QGraphicsTextItem *textValueItem = scene->addText("Value:");
    textValueItem->setPos(-5*cellSize - 50, -yPointCoordHigher * cellSize - 20);
}

void MainWindow::drawGraphe(QGraphicsScene *scene, int cellSize) {
    QPen xAxisPen(Qt::white);
    scene->addLine(-5*cellSize, 5*cellSize, 25*cellSize, 5*cellSize, xAxisPen);

    Node* current = context.table->first;
    double prevX, prevY;
    int isFirst = 1;
    int modif = 1;

    if (atoi(context.column) > 5) {
        modif *= 10;
    }

    for (int x = -4*cellSize; x <= 23*cellSize; x += cellSize) {

        int year = 1989 + (5*cellSize + x) / cellSize;
        QGraphicsTextItem *textItem = scene->addText(QString::number(year));
        textItem->setPos(x, 4.5*cellSize);

        QGraphicsEllipseItem *marker = new QGraphicsEllipseItem(0, 0, 10, 10);
        marker->setBrush(Qt::white);
        marker->setPos(x-5,5*cellSize-5);
        scene->addItem(marker);

        while (current) {
            if (!strcmp(current->data.region, context.region)) {
                if (current->data.year == year) {
                    double y = 5*cellSize - getField(current,atoi(context.column))/modif * cellSize;
                    if (isFirst) {
                        prevX = x;
                        prevY = y;
                        isFirst = 0;
                    }
                    QGraphicsEllipseItem *dataMarker = new QGraphicsEllipseItem(0, 0, 10, 10);
                    if (getField(current,atoi(context.column)) == context.min) {
                        dataMarker->setBrush(Qt::blue);
                    } else if (getField(current,atoi(context.column)) == context.max) {
                        dataMarker->setBrush(Qt::yellow);
                    } else {
                        dataMarker->setBrush(Qt::red);
                    }
                    scene->addLine(x, y, prevX, prevY, QPen(Qt::red));
                    dataMarker->setPos(x-5,y-5);
                    scene->addItem(dataMarker);

                    prevX = x;
                    prevY = y;

                    QGraphicsTextItem *dataTextItem = scene->addText(QString::number(getField(current,atoi(context.column))));
                    dataTextItem->setPos(x - 20, y);

                    current = current->next;
                }
                break;
            } else {
                current = current->next;
            }
        }
    }
}
