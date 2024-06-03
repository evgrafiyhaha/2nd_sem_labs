#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->add0PushButton, &QPushButton::clicked, this, [this]() {output('0');});
    connect(ui->add1PushButton, &QPushButton::clicked, this, [this]() {output('1');});
    connect(ui->add2PushButton, &QPushButton::clicked, this, [this]() {output('2');});
    connect(ui->add3PushButton, &QPushButton::clicked, this, [this]() {output('3');});
    connect(ui->add4PushButton, &QPushButton::clicked, this, [this]() {output('4');});
    connect(ui->add5PushButton, &QPushButton::clicked, this, [this]() {output('5');});
    connect(ui->add6PushButton, &QPushButton::clicked, this, [this]() {output('6');});
    connect(ui->add7PushButton, &QPushButton::clicked, this, [this]() {output('7');});
    connect(ui->add8PushButton, &QPushButton::clicked, this, [this]() {output('8');});
    connect(ui->add9PushButton, &QPushButton::clicked, this, [this]() {output('9');});
    connect(ui->plusPushButton, &QPushButton::clicked, this, [this]() {output('+');});
    connect(ui->minusPushButton, &QPushButton::clicked, this, [this]() {output('-');});
    connect(ui->dividePushButton, &QPushButton::clicked, this, [this]() {output('/');});
    connect(ui->multiplyPushButton, &QPushButton::clicked, this, [this]() {output('*');});
    connect(ui->addDotPushButton, &QPushButton::clicked, this, [this]() {output('.');});
    connect(ui->openParenthesisPushButton, &QPushButton::clicked, this, [this]() {output('(');});
    connect(ui->closeParenthesisPushButton, &QPushButton::clicked, this, [this]() {output(')');});
    connect(ui->clearPushButton, &QPushButton::clicked, this, &MainWindow::clear);
    connect(ui->equalPushButton, &QPushButton::clicked, this, &MainWindow::calculate);
    connect(ui->delPushButton, &QPushButton::clicked, this, &MainWindow::deleteChar);

    ui->outputLabel->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deleteChar() {
    if (expression != SYNTAX_ERROR && expression != MATH_ERROR) {
        expression.chop(1);
        ui->outputLabel->setText(expression);
    } else {
        clear();
    }
}

void MainWindow::output(char character) {
    if (expression == SYNTAX_ERROR || expression == MATH_ERROR) {
        expression = "";
    }
    expression+=character;
    ui->outputLabel->setText(expression);
}

void MainWindow::clear() {
    expression = "";
    ui->outputLabel->setText(expression);
}

void MainWindow::calculate() {
    std::string answer = Facade::calculate(expression.toStdString());
    expression = QString::fromStdString(answer);
    ui->outputLabel->setText(expression);
}
