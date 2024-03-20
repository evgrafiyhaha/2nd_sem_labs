#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->translateButton, &QPushButton::clicked, this, &MainWindow::onTranslateClicked);
    connect(ui->bufferButton, &QPushButton::clicked, this, &MainWindow::onBufferButtonClicked);
    connect(ui->switchButton, &QPushButton::clicked, this, &MainWindow::onSwitchButtonClicked);
    doOperation(Initialization, &context, NULL);
    updateLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTranslateClicked() {
    AppParams* param = (AppParams*) malloc(sizeof(AppParams));
    strcpy(param->inputValue, ui->inputEdit->text().toStdString().c_str());
    param->inNumberSystem = ui->comboBoxInput->currentText().toInt();
    param->outNumberSystem = ui->comboBoxOutput->currentText().toInt();
    doOperation(Translate, &context, param);
    updateLabels();
    free(param);
}

void MainWindow::onBufferButtonClicked(){
    QClipboard* clipboard = QGuiApplication::clipboard();
    QString textToClipboard = ui->outputLabel->text();
    clipboard->setText(textToClipboard);
}

void MainWindow::onSwitchButtonClicked(){
    AppParams* param = (AppParams*) malloc(sizeof(AppParams));
    strcpy(param->inputValue, ui->inputEdit->text().toStdString().c_str());
    param->inNumberSystem = ui->comboBoxInput->currentText().toInt();
    param->outNumberSystem = ui->comboBoxOutput->currentText().toInt();
    doOperation(Switch, &context, param);
    updateLabels();
    if (context.errorData == Error_Code_0) {
        ui->inputEdit->setText(QString::fromStdString(context.inputValue));
        ui->outputLabel->setText(QString::fromStdString(context.currentValue));
        ui->comboBoxInput->setCurrentText(QString::number(context.inNumberSystem));
        ui->comboBoxOutput->setCurrentText(QString::number(context.outNumberSystem));
    }
}

void MainWindow::updateLabels() {
    ui->outputLabel->setText(QString::fromStdString(context.currentValue));
    errorCodeHandler(&context);
}

void MainWindow::errorCodeHandler(AppContext* context) {
    char* errorText = " ";
    switch(context->errorData){
    case Error_Code_0:
        errorText = ERROR_CODE_0_TEXT;
        break;
    case Error_Code_1:
        errorText = ERROR_CODE_1_TEXT;
        break;
    case Error_Code_2:
        errorText = ERROR_CODE_2_TEXT;
        break;
    case Error_Code_3:
        errorText = ERROR_CODE_3_TEXT;
        break;
    }
    ui->errorLabel->setText(errorText);
}
