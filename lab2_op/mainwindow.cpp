#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->selectButton,&QPushButton::clicked,this,&MainWindow::on_selectFileButton_clicked);
    connect(ui->loadDataButton,&QPushButton::clicked,this,&MainWindow::on_loadDataButton_clicked);
    connect(ui->calculateMetricsButton,&QPushButton::clicked,this,&MainWindow::on_calculateMetricsButton_clicked);
    doOperation(Initialization, &context, NULL);
    updateLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectFileButton_clicked() {
    AppParams param;
    QString fileName = QFileDialog::getOpenFileName(this,tr("Выберите CSV файл"), "", tr("CSV файлы (*.csv);;Все файлы (*.*)"));
    std::string stdStr = fileName.toStdString();
    const char* cStr = stdStr.c_str();
    strcpy(param.fileName, cStr);

    doOperation(CopyFileName,&context, &param);
    qDebug() << "param address: " << cStr;
}

void MainWindow::on_loadDataButton_clicked() {
    AppParams param;

    std::string stdStrRegion = ui->regionLineEdit->text().toStdString();
    const char* cStrRegion = stdStrRegion.c_str();
    strcpy(param.region, cStrRegion);

    doOperation(CopyRegion,&context,&param);

    if (strcmp(context.fileName,"")) {
        doOperation(Loading,&context,NULL);
    } else {
        context.errorData = FileNotChosenError;
    }
    updateLabels();
}

void MainWindow::updateLabels() {

    if (context.table != NULL) {
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(7);
        QStringList headers;
        headers << "Year" << "Region" << "Natural Population Growth" << "Birth Rate" << "Death Rate" << "General Demographic Weight" << "Urbanisation";
        ui->tableWidget->setHorizontalHeaderLabels(headers);

        Node* current = context.table->first;
        int row = 0;
        if (!strcmp(context.region,"")) {
            ui->tableWidget->setRowCount(context.numberOfSuccessLines);
            while (current) {
                setRow(current,row);
                current = current->next;
                ++row;
            }
        } else {
            while (current) {
                if (!strcmp(current->data.region,context.region)) {
                    ui->tableWidget->insertRow(row);
                    setRow(current,row);
                    ++row;
                }
            current = current->next;
            }
        }
        if (row != 0) {
            ui->tableWidget->show();
        } else {
            context.errorData = ZeroRowsError;
        }
    }
    ui->minLabel->setText(QString::number(context.min));
    ui->maxLabel->setText(QString::number(context.max));
    ui->medianLabel->setText(QString::number(context.median));
    ui->numberOfLinesLabel->setText(QString::number(context.numberOfLines));
    ui->errorLinesLabel->setText(QString::number(context.numberOfErrorLines));
    ui->successLinesLabel->setText(QString::number(context.numberOfSuccessLines));
    errorCodeHandler();
}

void MainWindow::on_calculateMetricsButton_clicked() {
    AppParams param;

    std::string stdStrRegion = ui->regionLineEdit->text().toStdString();
    const char* cStrRegion = stdStrRegion.c_str();
    strcpy(param.region, cStrRegion);

    std::string stdStrColumn = ui->columnNumLineEdit->text().toStdString();
    const char* cStrColumn = stdStrColumn.c_str();
    strcpy(param.column, cStrColumn);

    doOperation(CopyRegion,&context,&param);
    doOperation(CopyIndex,&context,&param);
    if (context.table != NULL) {
        doOperation(Calculation,&context,NULL);
        updateLabels();
    } else {
        context.errorData = EmptyTableError;
    }
}

void MainWindow::errorCodeHandler() {
    char* errorText = " ";
    switch(context.errorData){
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
    case FileNotChosenError:
        errorText = FILE_NOT_CHOSEN_ERROR;
        break;
    case ZeroRowsError:
        errorText = ZERO_ROWS_ERROR;
        break;
    case EmptyTableError:
        errorText = EMPTY_TABLE_ERROR;
        break;
    }
    ui->errorLabel->setText(errorText);
    context.errorData = NoErrors;
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
