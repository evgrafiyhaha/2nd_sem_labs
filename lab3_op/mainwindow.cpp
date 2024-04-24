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
    if (context.errorData == NoErrors && strcmp(context.region,"")) {
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

void MainWindow::setRow(Node* current, int row) {
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(current->data.year)));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString(current->data.region)));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(current->data.naturalPopulationGrowth)));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(current->data.birthRate)));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(current->data.deathRate)));
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(current->data.generalDemographicWeight)));
    ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(current->data.urbanisation)));
}


double MainWindow::getField(Node* p, int column) {
    column--;
    double field = 0;
    switch(column) {
    case Year:
        field = p->data.year;
        break;
    case NaturalPopulationGrowth:
        field = p->data.naturalPopulationGrowth;
        break;
    case BirthRate:
        field = p->data.birthRate;
        break;
    case DeathRate:
        field = p->data.deathRate;
        break;
    case GeneralDemographicWeight:
        field = p->data.generalDemographicWeight;
        break;
    case Urbanisation:
        field = p->data.urbanisation;
        break;
    }
    return field;
}

void MainWindow::setGraphic() {
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    while(true) {
        if (context.cellSize * (OY_LENGTH + SPACER) > ui->graphicsView->height() || context.cellSize * (findMaxYear() - findMinYear() + 1 + SPACER) > ui->graphicsView->width()) {
            context.cellSize--;
        } else {
            break;
        }
    }
    while(true) {
        if (context.cellSize * (OY_LENGTH + SPACER) > ui->graphicsView->height() || context.cellSize * (findMaxYear() - findMinYear() + 1 + SPACER) > ui->graphicsView->width()) {
            context.cellSize--;
            break;
        } else {
            context.cellSize++;
        }
    }
    int OYxValue = -5*context.cellSize;
    int OXyValue = 5*context.cellSize;

    drawOY(scene, OYxValue, OXyValue);

    drawOXAndGraphic(scene, OYxValue, OXyValue);
}

void MainWindow::drawOY(QGraphicsScene *scene, int OYxValue, int OXyValue) {

    QPen yAxisPen(Qt::white);
    double yPointCoordHigher = -10;
    double yPointCoordLower = 5;

    scene->addLine(OYxValue, yPointCoordLower * context.cellSize, OYxValue, yPointCoordHigher * context.cellSize, yAxisPen);
    double mstb = (yPointCoordHigher - yPointCoordLower) / OY_NUMBER_OF_POINTS * context.cellSize;
    double scale = findScale();

    double yCounter = context.min;
    int yCurr = OXyValue;

    for (int y = 0; y <= OY_NUMBER_OF_POINTS; y++) {
        QGraphicsEllipseItem *markerY = new QGraphicsEllipseItem(0, 0, context.cellSize/4, context.cellSize/4);
        markerY->setBrush(Qt::white);
        markerY->setPos(OYxValue - context.cellSize/8, yCurr);
        scene->addItem(markerY);

        QGraphicsTextItem *textItemY = scene->addText(QString::number(yCounter));
        textItemY->setPos(OYxValue - context.cellSize, yCurr);

        yCurr += mstb;
        yCounter += scale;
    }

    QGraphicsTextItem *textValueItem = scene->addText("Values:");
    textValueItem->setPos(OYxValue - context.cellSize,  (yPointCoordHigher - 1) * (context.cellSize));
}

void MainWindow::drawOXAndGraphic(QGraphicsScene *scene, int OYxValue, int OXyValue) {

    int OXMaxValue = (findMaxYear() - findMinYear() - 4) * context.cellSize;
    QPen xAxisPen(Qt::white);
    scene->addLine(OYxValue, OXyValue, OXMaxValue, OXyValue, xAxisPen);

    QGraphicsTextItem *textValueItem = scene->addText("Years:");
    textValueItem->setPos(OYxValue - context.cellSize,  OXyValue + context.cellSize/4);

    Node* current = context.table->first;
    double prevX, prevY;
    int isFirst = 1;

    for (int x = OYxValue + context.cellSize; x <= OXMaxValue; x += context.cellSize) {

        int year = findMinYear() + (4 * context.cellSize + x) / context.cellSize;
        QGraphicsTextItem *textItem = scene->addText(QString::number(year));
        textItem->setPos(x, 4.5 * context.cellSize);

        QGraphicsEllipseItem *marker = new QGraphicsEllipseItem(0, 0, context.cellSize/4, context.cellSize/4);
        marker->setBrush(Qt::white);
        marker->setPos(x - context.cellSize/8, OXyValue - context.cellSize/8);
        scene->addItem(marker);

        current = drawGraphic(scene, current, year, x, OXyValue, &isFirst, &prevX, &prevY);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    if (context.errorData == NoErrors && strcmp(context.region,"")) {
        setGraphic();
    }
}

Node* MainWindow::drawGraphic(QGraphicsScene *scene, Node* current, int year, int x,  int OXyValue, int* isFirst, double* prevX, double* prevY) {
    double coordYMax =(context.max - context.min);
    double modif = fabs((OY_LENGTH) / coordYMax);

    while (current) {
        if (!strcmp(current->data.region, context.region)) {
            if (current->data.year == year) {
                double y = OXyValue - (getField(current, atoi(context.column)) - context.min) * modif * context.cellSize;
                if (*isFirst) {
                    *prevX = x;
                    *prevY = y;
                    *isFirst = 0;
                }
                QGraphicsEllipseItem *dataMarker = new QGraphicsEllipseItem(0, 0, context.cellSize/4, context.cellSize/4);
                if (getField(current, atoi(context.column)) == context.min) {
                    dataMarker->setBrush(Qt::blue);
                } else if (getField(current, atoi(context.column)) == context.max) {
                    dataMarker->setBrush(Qt::yellow);
                }  else {
                    dataMarker->setBrush(Qt::red);
                }
                scene->addLine(x, y, *prevX, *prevY, QPen(Qt::red));
                dataMarker->setPos(x - context.cellSize/8, y-context.cellSize/8);
                scene->addItem(dataMarker);

                *prevX = x;
                *prevY = y;

                QGraphicsTextItem *dataTextItem = scene->addText(QString::number(getField(current, atoi(context.column))));
                dataTextItem->setPos(x - context.cellSize/2, y);

                return current->next;
            }
        } else {
            current = current->next;
        }
    }
}

double MainWindow::findScale() {
    return (context.max - context.min) / OY_NUMBER_OF_POINTS;
}

int MainWindow::findMinYear() {
    Node* p = context.table->first;
    int min = BIG_NUM_FOR_COMP;

    do {
        if (!strcmp(p->data.region, context.region)) {
            if (p->data.year < min)
                min = p->data.year;
        }
        p = p->next;
    } while (p != NULL);
    return min;
}

int MainWindow::findMaxYear() {
    Node* p = context.table->first;
    int max = 0;

    do {
        if (!strcmp(p->data.region, context.region)) {
            if (p->data.year > max)
                max = p->data.year;
        }
        p = p->next;
    } while (p != NULL);
    return max;
}
