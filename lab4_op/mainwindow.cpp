#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->selectButton, &QPushButton::clicked, this, &MainWindow::on_selectFileButton_clicked);
    connect(ui->loadDataButton, &QPushButton::clicked, this, &MainWindow::on_loadDataButton_clicked);

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

    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &MainWindow::onMovementTimeout);
    rotationTimer = new QTimer(this);
    connect(rotationTimer, &QTimer::timeout, this, &MainWindow::onRotationTimeout);
    scalingTimer = new QTimer(this);
    connect(scalingTimer, &QTimer::timeout, this, &MainWindow::onScalingTimeout);

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
    delete movementTimer;
    delete rotationTimer;
    delete scalingTimer;
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

    std::string stdStrNormalizationFrom = ui->normalizationFromLabel->text().toStdString();
    const char* cStrNormalizationFrom  = stdStrNormalizationFrom.c_str();
    strcpy(param.normalizationFrom, cStrNormalizationFrom);

    doOperation(SetnormalizationFrom,&context,&param);

    std::string stdStrNormalizationTo = ui->normalizationToLabel->text().toStdString();
    const char* cStrNormalizationTo = stdStrNormalizationTo.c_str();
    strcpy(param.normalizationTo, cStrNormalizationTo);

    doOperation(SetnormalizationTo,&context,&param);

    doOperation(Loading,&context, NULL);
    if ((context.normalizationFrom < context.normalizationTo && context.normalizationFrom >= 0 && context.normalizationTo >= 0)) {
        doOperation(Normalizing,&context,NULL);
    }
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
    if (((context.normalizationFrom < context.normalizationTo && context.normalizationFrom >= 0 && context.normalizationTo >= 0) || (context.normalizationFrom == 0 && context.normalizationTo == 0))) {
        QGraphicsScene *scene = new QGraphicsScene(this);
        ui->graphicsView->setScene(scene);
        drawModel(scene);
    } else {
        context.errorData = NormalizationError;
    }
}

double MainWindow::findMax(coordinates param) {
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

double MainWindow::findMin(coordinates param) {
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

    double y_perspective, z_perspective;
    double x0 = 20, y0 = 0, z0 = 0;
    double prevY, prevZ;
    int counter = 0;

    double d = sqrt(pow(context.centerPoint.x - x0, 2) + pow(context.centerPoint.y - y0, 2) + pow(context.centerPoint.z - z0, 2));

    //ось вращения
    //scene->addLine((context.centerPoint.y*d)/(context.centerPoint.x + d)*context.cellSize,0,(context.centerPoint.y*d)/(context.centerPoint.x+d)*context.cellSize,-(30*d)/(context.centerPoint.x+d)*context.cellSize, QPen(Qt::green));

    qDebug() << context.centerPoint.x << context.centerPoint.y << context.centerPoint.z;
    while (current) {
        y_perspective = (current->data.y * d) / (current->data.x + d);
        z_perspective = (current->data.z * d) / (current->data.x + d);
        QGraphicsEllipseItem *dataMarker = new QGraphicsEllipseItem(0, 0, context.cellSize/4, context.cellSize/4);
        dataMarker->setBrush(QColorConstants::Svg::pink);
        dataMarker->setPos(y_perspective*context.cellSize - context.cellSize/8, -z_perspective*context.cellSize - context.cellSize/8);
        scene->addItem(dataMarker);

        if (counter < context.lineLength) {
            pushEnd(prevYPointList, current->data);
        } else {
            Point prevYPoint = findPrev(prevYPointList,counter);
            pushEnd(prevYPointList,current->data);
            double prevYYPerspective = (prevYPoint.y * d) / (prevYPoint.x + d);
            double prevYZperspective = (prevYPoint.z * d) / (prevYPoint.x + d);
            scene->addLine(y_perspective*context.cellSize, -z_perspective*context.cellSize, prevYYPerspective * context.cellSize, -prevYZperspective * context.cellSize, QPen(QColorConstants::Svg::pink));
        }
        if ((current != context.coordinates->first) && counter % context.lineLength != 0) {
            scene->addLine(y_perspective * context.cellSize, -z_perspective * context.cellSize, prevY * context.cellSize, -prevZ * context.cellSize, QPen(QColorConstants::Svg::pink));
        }

        prevY = y_perspective;
        prevZ = z_perspective;
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
    movementTimer->start(TIMER_TIME);
    AppParams param;
    param.currentCoordinateOperation = 3;
    param.direction = 1;
    doOperation(ChangeCoordinate,&context,&param);
    doOperation(ChangeDirection,&context,&param);
}

void MainWindow::onMoveUpButtonReleased() {
    movementTimer->stop();
}

void MainWindow::onMovementTimeout() {
    doOperation(Movement,&context,NULL);
    updateLabels();
}

void MainWindow::onMoveDownButtonPressed() {
    movementTimer->start(TIMER_TIME);
    AppParams param;
    param.currentCoordinateOperation = 3;
    param.direction = -1;
    doOperation(ChangeCoordinate,&context,&param);
    doOperation(ChangeDirection,&context,&param);
}
void MainWindow::onMoveDownButtonReleased() {
    movementTimer->stop();
}

void MainWindow::onMoveLeftButtonPressed() {
    movementTimer->start(TIMER_TIME);
    AppParams param;
    param.currentCoordinateOperation = 2;
    param.direction = -1;
    doOperation(ChangeCoordinate,&context,&param);
    doOperation(ChangeDirection,&context,&param);
}
void MainWindow::onMoveLeftButtonReleased() {
    movementTimer->stop();
}

void MainWindow::onMoveRightButtonPressed() {
    movementTimer->start(TIMER_TIME);
    AppParams param;
    param.currentCoordinateOperation = 2;
    param.direction = 1;
    doOperation(ChangeCoordinate,&context,&param);
    doOperation(ChangeDirection,&context,&param);
}
void MainWindow::onMoveRightButtonReleased() {
    movementTimer->stop();
}

void MainWindow::onMoveBackButtonPressed() {
    movementTimer->start(TIMER_TIME);
    AppParams param;
    param.currentCoordinateOperation = 1;
    param.direction = -1;
    doOperation(ChangeCoordinate,&context,&param);
    doOperation(ChangeDirection,&context,&param);
}

void MainWindow::onMoveBackButtonReleased() {
    movementTimer->stop();
}

void MainWindow::onMoveForwardButtonPressed() {
    movementTimer->start(TIMER_TIME);
    AppParams param;
    param.currentCoordinateOperation = 1;
    param.direction = 1;
    doOperation(ChangeCoordinate,&context,&param);
    doOperation(ChangeDirection,&context,&param);
}

void MainWindow::onMoveForwardButtonReleased() {
    movementTimer->stop();
}

void MainWindow::onRotateUpButtonPressed() {
    rotationTimer->start(TIMER_TIME);
    AppParams param;
    param.currentCoordinateOperation = 2;
    param.direction = 1;
    doOperation(ChangeCoordinate,&context,&param);
    doOperation(ChangeDirection,&context,&param);
}

void MainWindow::onRotateUpButtonReleased() {
    rotationTimer->stop();
}

void MainWindow::onRotationTimeout() {
    doOperation(Rotation,&context,NULL);
    updateLabels();
}

void MainWindow::onRotateDownButtonPressed() {
    rotationTimer->start(TIMER_TIME);
    AppParams param;
    param.currentCoordinateOperation = 2;
    param.direction = -1;
    doOperation(ChangeCoordinate,&context,&param);
    doOperation(ChangeDirection,&context,&param);
}

void MainWindow::onRotateDownButtonReleased() {
    rotationTimer->stop();
}

void MainWindow::onRotateLeftButtonPressed() {
    rotationTimer->start(TIMER_TIME);
    AppParams param;
    param.currentCoordinateOperation = 3;
    param.direction = -1;
    doOperation(ChangeCoordinate,&context,&param);
    doOperation(ChangeDirection,&context,&param);
}

void MainWindow::onRotateLeftButtonReleased() {
    rotationTimer->stop();
}

void MainWindow::onRotateRightButtonPressed() {
    rotationTimer->start(TIMER_TIME);
    AppParams param;
    param.currentCoordinateOperation = 3;
    param.direction = 1;
    doOperation(ChangeCoordinate,&context,&param);
    doOperation(ChangeDirection,&context,&param);
}

void MainWindow::onRotateRightButtonReleased() {
    rotationTimer->stop();
}

void MainWindow::onScalingUpButtonPressed() {
    scalingTimer->start(TIMER_TIME);
    AppParams param;

    param.direction = 2;
    doOperation(ChangeDirection,&context,&param);
}

void MainWindow::onScalingUpButtonReleased() {
    scalingTimer->stop();
}

void MainWindow::onScalingDownButtonPressed() {
    scalingTimer->start(TIMER_TIME);
    AppParams param;

    param.direction = 1;
    doOperation(ChangeDirection,&context,&param);
}

void MainWindow::onScalingDownButtonReleased() {
    scalingTimer->stop();
}

void MainWindow::onScalingTimeout() {
    doOperation(Scaling,&context,NULL);
    updateLabels();
}
