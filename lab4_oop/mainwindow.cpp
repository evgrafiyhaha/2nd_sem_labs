#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , buttonGroup(new QButtonGroup(this))
{
    ui->setupUi(this);
    connect(ui->selectButton, &QPushButton::clicked, this, &MainWindow::onSelectFileButtonClicked);
    connect(ui->DrawSceneButton, &QPushButton::clicked, this, &MainWindow::onDrawSceneButtonClicked);
    connect(ui->DoOperationPushButton, &QPushButton::clicked, this, &MainWindow::OnDoOperationButtonClicked);

    buttonGroup->addButton(ui->ScaleRadioButton, 1);
    buttonGroup->addButton(ui->MoveRadioButton, 2);
    buttonGroup->addButton(ui->RotateRadioButton, 3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSelectFileButtonClicked() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выберите CSV файл"), "", tr("CSV файлы (*.csv);;Все файлы (*.*)"));

    double min = ui->MinLabel->text().toDouble();
    double max = ui->MaxLabel->text().toDouble();
    NormalizationParameters normParams(min,max);

    FacadeOperationResult result = facade.LoadScene(filePath.toStdString(), normParams);
    if (result.isSucces()) {
        ui->fileNameLabel->setText(filePath);
    }
    ui->ErrorLabel->setText(result.getErrorMessage().c_str());
}

void MainWindow::onDrawSceneButtonClicked() {
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    facade.setQTScene(scene);

    FacadeOperationResult result = facade.DrawScene();
    ui->ErrorLabel->setText(result.getErrorMessage().c_str());
}

void MainWindow::OnDoOperationButtonClicked() {
    QAbstractButton *checkedButton = buttonGroup->checkedButton();
    bool convertable;
    double xValue = ui->XlineEdit->text().toDouble(&convertable);
    double yValue = ui->YlineEdit->text().toDouble(&convertable);
    double zValue = ui->ZlineEdit->text().toDouble(&convertable);

    QString errorText;
    if (checkedButton) {
        if (!convertable) {
            errorText = NOT_CONVERTABLE_ERROR;
        } else {
            std::string operation = checkedButton->text().toStdString();
            FacadeOperationResult result = facade.DoOPeration(operation,xValue,yValue,zValue);
            errorText = QString::fromStdString(result.getErrorMessage());
        }
    } else {
        errorText = NO_OPERATION_ERROR;
    }
    ui->ErrorLabel->setText(errorText);
}
