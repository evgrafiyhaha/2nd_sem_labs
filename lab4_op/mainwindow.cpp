#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->selectButton, &QPushButton::clicked, this, &MainWindow::onSelectFileButtonClicked);
    connect(ui->loadDataButton, &QPushButton::clicked, this, &MainWindow::onLoadDataButtonClicked);

    connect(ui->moveUpButton, &QPushButton::pressed, this, &MainWindow::onMoveUpButtonPressed);
    connect(ui->moveUpButton, &QPushButton::released, this, &MainWindow::onMoveUpButtonReleased);

    connect(ui->moveDownButton, &QPushButton::pressed, this, &MainWindow::onMoveDownButtonPressed);
    connect(ui->moveDownButton, &QPushButton::released, this, &MainWindow::onMoveDownButtonReleased);

    connect(ui->moveLeftButton, &QPushButton::pressed, this, &MainWindow::onMoveLeftButtonPressed);
    connect(ui->moveLeftButton, &QPushButton::released, this, &MainWindow::onMoveLeftButtonReleased);

    connect(ui->moveRightButton, &QPushButton::pressed, this, &MainWindow::onMoveRightButtonPressed);
    connect(ui->moveRightButton, &QPushButton::released, this, &MainWindow::onMoveRightButtonReleased);

    connect(ui->moveBackButton, &QPushButton::pressed, this, &MainWindow::onMoveBackButtonPressed);
    connect(ui->moveBackButton, &QPushButton::released, this, &MainWindow::onMoveBackButtonReleased);

    connect(ui->moveForwardButton, &QPushButton::pressed, this, &MainWindow::onMoveForwardButtonPressed);
    connect(ui->moveForwardButton, &QPushButton::released, this, &MainWindow::onMoveForwardButtonReleased);

    connect(ui->rotateUpButton, &QPushButton::pressed, this, &MainWindow::onRotateUpButtonPressed);
    connect(ui->rotateUpButton, &QPushButton::released, this, &MainWindow::onRotateUpButtonReleased);

    connect(ui->rotateDownButton, &QPushButton::pressed, this, &MainWindow::onRotateDownButtonPressed);
    connect(ui->rotateDownButton, &QPushButton::released, this, &MainWindow::onRotateDownButtonReleased);

    connect(ui->rotateLeftButton, &QPushButton::pressed, this, &MainWindow::onRotateLeftButtonPressed);
    connect(ui->rotateLeftButton, &QPushButton::released, this, &MainWindow::onRotateLeftButtonReleased);

    connect(ui->rotateRightButton, &QPushButton::pressed, this, &MainWindow::onRotateRightButtonPressed);
    connect(ui->rotateRightButton, &QPushButton::released, this, &MainWindow::onRotateRightButtonReleased);

    movementXForwardTimer = new QTimer(this);
    connect(movementXForwardTimer, &QTimer::timeout, this, &MainWindow::movementXForwardTimerTimeout);
    movementXBackTimer = new QTimer(this);
    connect(movementXBackTimer, &QTimer::timeout, this, &MainWindow::movementXBackTimerTimeout);

    movementZUpTimer = new QTimer(this);
    connect(movementZUpTimer, &QTimer::timeout, this, &MainWindow::movementZUpTimerTimeout);
    movementZDownTimer = new QTimer(this);
    connect(movementZDownTimer, &QTimer::timeout, this, &MainWindow::movementZDownTimerTimeout);

    movementYRightTimer = new QTimer(this);
    connect(movementYRightTimer, &QTimer::timeout, this, &MainWindow::movementYRightTimerTimeout);
    movementYLeftTimer = new QTimer(this);
    connect(movementYLeftTimer, &QTimer::timeout, this, &MainWindow::movementYLeftTimerTimeout);

    rotationZUpTimer = new QTimer(this);
    connect(rotationZUpTimer, &QTimer::timeout, this, &MainWindow::rotationZUpTimerTimeout);
    rotationZDownTimer = new QTimer(this);
    connect(rotationZDownTimer, &QTimer::timeout, this, &MainWindow::rotationZDownTimerTimeout);
    rotationYLeftTimer = new QTimer(this);
    connect(rotationYLeftTimer, &QTimer::timeout, this, &MainWindow::rotationYLeftTimeout);
    rotationYRightTimer = new QTimer(this);
    connect(rotationYRightTimer, &QTimer::timeout, this, &MainWindow::rotationYRightTimerTimeout);

    scalingUpTimer = new QTimer(this);
    connect(scalingUpTimer, &QTimer::timeout, this, &MainWindow::scalingUpTimerTimeout);
    scalingDownTimer = new QTimer(this);
    connect(scalingDownTimer, &QTimer::timeout, this, &MainWindow::scalingDownTimerTimeout);

    connect(ui->scalingDownButton, &QPushButton::pressed, this, &MainWindow::onScalingDownButtonPressed);
    connect(ui->scalingDownButton, &QPushButton::released, this, &MainWindow::onScalingDownButtonReleased);

    connect(ui->scalingUpButton, &QPushButton::pressed, this, &MainWindow::onScalingUpButtonPressed);
    connect(ui->scalingUpButton, &QPushButton::released, this, &MainWindow::onScalingUpButtonReleased);

    doOperation(Initialization, &context, NULL);
    updateLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete movementXForwardTimer;
    delete movementXBackTimer;
    delete movementZUpTimer;
    delete movementZDownTimer;
    delete movementYRightTimer;
    delete movementYLeftTimer;
    delete rotationZUpTimer;
    delete rotationZDownTimer;
    delete rotationYLeftTimer;
    delete rotationYRightTimer;
    delete scalingUpTimer;
    delete scalingDownTimer;
}

void MainWindow::onSelectFileButtonClicked() {
    AppParams param;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Выберите CSV файл"), "", tr("CSV файлы (*.csv);;Все файлы (*.*)"));
    std::string stdStr = fileName.toStdString();
    const char* cStr = stdStr.c_str();
    strcpy(param.fileName, cStr);

    doOperation(SetFileName, &context, &param);

    ui->fileNameLabel->setText(context.fileName);
}

void MainWindow::onLoadDataButtonClicked() {
    AppParams param;

    doOperation(Loading,&context, NULL);

    std::string stdStrNormalizationFrom = ui->normalizationFromLabel->text().toStdString();
    const char* cStrNormalizationFrom  = stdStrNormalizationFrom.c_str();
    strcpy(param.normalizationFrom, cStrNormalizationFrom);

    doOperation(SetnormalizationFrom,&context,&param);

    std::string stdStrNormalizationTo = ui->normalizationToLabel->text().toStdString();
    const char* cStrNormalizationTo = stdStrNormalizationTo.c_str();
    strcpy(param.normalizationTo, cStrNormalizationTo);

    doOperation(SetnormalizationTo,&context,&param);

    doOperation(Normalizing,&context,NULL);

    updateLabels();
}

void MainWindow::updateLabels() {
    if (context.coordinates != NULL) {
        showModel();
    }
    ui->numberOfLinesLabel->setText(QString::number(context.numberOfLines));
    ui->errorLinesLabel->setText(QString::number(context.numberOfErrorLines));
    ui->successLinesLabel->setText(QString::number(context.numberOfSuccessLines));
    errorCodeHandler();

}

void MainWindow::showModel() {
    if (context.errorData != NormalizationError) {
        QGraphicsScene *scene = new QGraphicsScene(this);
        ui->graphicsView->setScene(scene);
        drawModel(scene);
    }
}

double MainWindow::findMax(Coordinates param) {
    Node* current = context.coordinates->first;
    double max = 0;
    while (current) {
        double value = 0;
        switch (param) {
        case X:
            value = current->data.x;
            break;
        case Y:
            value = current->data.y;
            break;
        case Z:
            value = current->data.z;
            break;
        default:
            break;
        }
        if (value > max) {
            max = value;
        }
        current = current->next;
    }
    return max;
}

double MainWindow::findMin(Coordinates param) {
    Node* current = context.coordinates->first;
    double min = BIG_NUM_FOR_COMP;
    while (current) {
        double value = 0;
        switch (param) {
        case X:
            value = current->data.x;
            break;
        case Y:
            value = current->data.y;
            break;
        case Z:
            value = current->data.z;
            break;
        default:
            break;
        }
        if (value < min) {
            min = value;
        }
        current = current->next;
    }
    return min;
}

void MainWindow::drawModel(QGraphicsScene *scene) {
    Node* current = context.coordinates->first;

    List* prevYPointList = (List*)malloc(sizeof(List));
    prevYPointList->first = NULL;

    double Yperspective, Zperspective;
    double x0 = 300, y0 = 0, z0 = 0;
    double prevY, prevZ;
    int counter = 0;

    double d = sqrt(pow(context.centerPoint.x - x0, 2) + pow(context.centerPoint.y - y0, 2) + pow(context.centerPoint.z - z0, 2));


    drawShowcasePoint(scene,x0);

    while (current) {
        Yperspective = (current->data.y * d) / (current->data.x + d);
        Zperspective = (current->data.z * d) / (current->data.x + d);
        QGraphicsEllipseItem *dataMarker = new QGraphicsEllipseItem(0, 0, CELL_SIZE/4, CELL_SIZE/4);
        dataMarker->setBrush(QColorConstants::Svg::pink);
        dataMarker->setPos(Yperspective*CELL_SIZE - CELL_SIZE/8, -Zperspective*CELL_SIZE - CELL_SIZE/8);
        scene->addItem(dataMarker);

        if (counter < context.lineLength) {
            pushEnd(prevYPointList, current->data);
        } else {
            Point prevYPoint = findPrev(prevYPointList,counter);
            pushEnd(prevYPointList,current->data);
            double prevYYPerspective = (prevYPoint.y * d) / (prevYPoint.x + d);
            double prevYZperspective = (prevYPoint.z * d) / (prevYPoint.x + d);
            scene->addLine(Yperspective*CELL_SIZE, -Zperspective*CELL_SIZE, prevYYPerspective * CELL_SIZE, -prevYZperspective * CELL_SIZE, QPen(QColorConstants::Svg::pink));
        }
        if ((current != context.coordinates->first) && counter % context.lineLength != 0) {
            scene->addLine(Yperspective * CELL_SIZE, -Zperspective * CELL_SIZE, prevY * CELL_SIZE, -prevZ * CELL_SIZE, QPen(QColorConstants::Svg::pink));
        }

        prevY = Yperspective;
        prevZ = Zperspective;
        current = current->next;
        counter++;
    }
    free(prevYPointList);
}

Point MainWindow::findPrev(List* prevPointsList, int counter) {
    Node* prevPointCurrent = prevPointsList->first;
    int index = counter - context.lineLength;
    int finder = 0;
    while (prevPointCurrent) {
        if (index == finder) {
            return prevPointCurrent->data;
        }
        prevPointCurrent = prevPointCurrent->next;
        finder++;
    }
}

void MainWindow::drawShowcasePoint(QGraphicsScene *scene, double x0) {
    double perY = 1/x0;
    double perZ = 1/x0;
    QGraphicsEllipseItem *dataMarker = new QGraphicsEllipseItem(0, 0, CELL_SIZE/4, CELL_SIZE/4);
    dataMarker->setBrush(QColorConstants::Svg::blue);
    dataMarker->setPos(perY*CELL_SIZE - CELL_SIZE/8, -perZ*CELL_SIZE - CELL_SIZE/8);
    scene->addItem(dataMarker);
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
    case EmptyFileNameError:
        errorText = FILE_NOT_CHOSEN_ERROR;
        break;
    case MemoryAllocationError:
        errorText = ALLOCATION_ERROR;
        break;
    case EmptyListError:
        errorText = EMPTY_LIST_ERROR;
        break;
    case NormalizationError:
        errorText = NORMAL_ERROR;
        break;
    }
    ui->errorLabel->setText(errorText);
}

void MainWindow::onMoveUpButtonPressed() {
    movementZUpTimer->start(TIMER_TIME);
}

void MainWindow::onMoveUpButtonReleased() {
    movementZUpTimer->stop();
}

void MainWindow::movementZUpTimerTimeout() {
    AppParams param;
    param.coordinateForOperation = Z;
    param.operationParam = 1;
    doOperation(Movement,&context,&param);
    updateLabels();
}

void MainWindow::onMoveDownButtonPressed() {
    movementZDownTimer->start(TIMER_TIME);
}
void MainWindow::onMoveDownButtonReleased() {
    movementZDownTimer->stop();
}

void MainWindow::movementZDownTimerTimeout() {
    AppParams param;
    param.coordinateForOperation = Z;
    param.operationParam = -1;
    doOperation(Movement,&context,&param);
    updateLabels();
}

void MainWindow::onMoveLeftButtonPressed() {
    movementYLeftTimer->start(TIMER_TIME);
}
void MainWindow::onMoveLeftButtonReleased() {
    movementYLeftTimer->stop();
}

void MainWindow::movementYLeftTimerTimeout() {
    AppParams param;
    param.coordinateForOperation = Y;
    param.operationParam = -1;
    doOperation(Movement,&context,&param);
    updateLabels();
}

void MainWindow::onMoveRightButtonPressed() {
    movementYRightTimer->start(TIMER_TIME);
}
void MainWindow::onMoveRightButtonReleased() {
    movementYRightTimer->stop();
}

void MainWindow::movementYRightTimerTimeout() {
    AppParams param;
    param.coordinateForOperation = Y;
    param.operationParam = 1;
    doOperation(Movement,&context,&param);
    updateLabels();
}

void MainWindow::onMoveBackButtonPressed() {
    movementXBackTimer->start(TIMER_TIME);
}

void MainWindow::onMoveBackButtonReleased() {
    movementXBackTimer->stop();
}

void MainWindow::movementXBackTimerTimeout() {
    AppParams param;
    param.coordinateForOperation = X;
    param.operationParam = -1;
    doOperation(Movement,&context,&param);
    updateLabels();

}

void MainWindow::onMoveForwardButtonPressed() {
    movementXForwardTimer->start(TIMER_TIME);
}

void MainWindow::onMoveForwardButtonReleased() {
    movementXForwardTimer->stop();
}

void MainWindow::movementXForwardTimerTimeout() {
    AppParams param;
    param.coordinateForOperation = X;
    param.operationParam = 1;
    doOperation(Movement,&context,&param);
    updateLabels();
}

void MainWindow::onRotateUpButtonPressed() {
    rotationZUpTimer->start(TIMER_TIME);
}

void MainWindow::onRotateUpButtonReleased() {
    rotationZUpTimer->stop();
}

void MainWindow::rotationZUpTimerTimeout() {
    AppParams param;
    param.coordinateForOperation = Y;
    param.operationParam = 1;
    doOperation(Rotation,&context,&param);
    updateLabels();
}

void MainWindow::onRotateDownButtonPressed() {
    rotationZDownTimer->start(TIMER_TIME);
}

void MainWindow::onRotateDownButtonReleased() {
    rotationZDownTimer->stop();
}

void MainWindow::rotationZDownTimerTimeout() {
    AppParams param;
    param.coordinateForOperation = Y;
    param.operationParam = -1;
    doOperation(Rotation,&context,&param);
    updateLabels();
}



void MainWindow::onRotateLeftButtonPressed() {
    rotationYLeftTimer->start(TIMER_TIME);
}

void MainWindow::onRotateLeftButtonReleased() {
    rotationYLeftTimer->stop();
}

void MainWindow::rotationYLeftTimeout() {
    AppParams param;
    param.coordinateForOperation = Z;
    param.operationParam = -1;
    doOperation(Rotation,&context,&param);
    updateLabels();
}


void MainWindow::onRotateRightButtonPressed() {
    rotationYRightTimer->start(TIMER_TIME);
}

void MainWindow::onRotateRightButtonReleased() {
    rotationYRightTimer->stop();
}

void MainWindow::rotationYRightTimerTimeout() {
    AppParams param;
    param.coordinateForOperation = Z;
    param.operationParam = 1;
    doOperation(Rotation,&context,&param);
    updateLabels();
}

void MainWindow::onScalingUpButtonPressed() {
    scalingUpTimer->start(TIMER_TIME);
}

void MainWindow::onScalingUpButtonReleased() {
    scalingUpTimer->stop();
}

void MainWindow::scalingUpTimerTimeout() {
    AppParams param;

    param.operationParam = 1.01;
    doOperation(Scaling,&context,&param);
    updateLabels();
}

void MainWindow::onScalingDownButtonPressed() {
    scalingDownTimer->start(TIMER_TIME);
}

void MainWindow::onScalingDownButtonReleased() {
    scalingDownTimer->stop();
}

void MainWindow::scalingDownTimerTimeout() {
    AppParams param;

    param.operationParam = 0.99;
    doOperation(Scaling,&context,&param);
    updateLabels();
}
