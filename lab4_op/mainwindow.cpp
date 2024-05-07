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
    if ((context.normalizationFrom < context.normalizationTo && context.normalizationFrom >= 0 && context.normalizationTo >= 0)) {
        QGraphicsScene *scene = new QGraphicsScene(this);
        ui->graphicsView->setScene(scene);

        drawNormedModel(scene);
    } else if ((context.normalizationFrom == 0 && context.normalizationTo == 0)) {
        QGraphicsScene *scene = new QGraphicsScene(this);
        ui->graphicsView->setScene(scene);

        drawModel(scene);
    } else {
        context.errorData = NormalizationError;
        qDebug() << context.normalizationTo;
        qDebug() << context.normalizationFrom;
    }
}

double MainWindow::findMax(int param) {
    Node* current = context.coordinates->first;
    double max = 0;
    while (current) {
        double value = 0;
        switch (param) {
        case 1:
            value = current->data.x;
            break;
        case 2:
            value = current->data.y;
            break;
        case 3:
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

double MainWindow::findMin(int param) {
    Node* current = context.coordinates->first;
    double min = BIG_NUM_FOR_COMP;
    while (current) {
        double value = 0;
        switch (param) {
        case 1:
            value = current->data.x;
            break;
        case 2:
            value = current->data.y;
            break;
        case 3:
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
/*
double MainWindow::findPerspectiveMax(int param) {
    Node* current = context.coordinates->first;
    double max = 0;
    while (current) {
        double value = 0;
        switch (param) {
        case 2:
            value = current->data.y;
            break;
        case 3:
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

double MainWindow::findPerspectiveMin(int param) {
    Node* current = context.coordinates->first;
    double min = BIG_NUM_FOR_COMP;
    while (current) {
        double value = 0;
        switch (param) {
        case 2:
            value = (current->data.y * d) / (current->data.x + d);
            break;
        case 3:
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
*/

void MainWindow::drawModel(QGraphicsScene *scene) {
    Node* current = context.coordinates->first;

    double y_perspective, z_perspective;
    double x0 = 20, y0 = 0, z0 = 0;
    double prevY = 0, prevZ = 0;
    double d;
    double max_distance = 0;

    while (current) {
        double distance = sqrt(pow(current->data.x - x0, 2) + pow(current->data.y - y0, 2) + pow(current->data.z - z0, 2));
        if (distance > max_distance)
            max_distance = distance;
        current = current->next;
    }

    d = max_distance;

    current = context.coordinates->first;
    while (current) {
        y_perspective = (current->data.y * d) / (current->data.x + d);
        z_perspective = (current->data.z * d) / (current->data.x + d);
        QGraphicsEllipseItem *dataMarker = new QGraphicsEllipseItem(0, 0, context.cellSize/4, context.cellSize/4);
        dataMarker->setBrush(Qt::red);
        dataMarker->setPos(y_perspective*context.cellSize - context.cellSize/8, -z_perspective*context.cellSize - context.cellSize/8);
        scene->addItem(dataMarker);

        if (current != context.coordinates->first) {
            scene->addLine(y_perspective*context.cellSize, -z_perspective*context.cellSize, prevY * context.cellSize, -prevZ * context.cellSize, QPen(Qt::red));
        }

        prevY = y_perspective;
        prevZ = z_perspective;
        current = current->next;
    }
}

void MainWindow::drawNormedModel(QGraphicsScene *scene) {
    Node* current = context.coordinates->first;

    double y_perspective, z_perspective;
    double x0 = normedValue(20,1), y0 = normedValue(0,2), z0 = normedValue(0,3);
    double prevY = 0, prevZ = 0;
    double d;
    double max_distance = 0;

    while (current) {
        double distance = sqrt(pow(normedValue(current->data.x,1) - x0, 2) + pow(normedValue(current->data.y,2) - y0, 2) + pow(normedValue(current->data.z,3) - z0, 2));
        if (distance > max_distance)
            max_distance = distance;
        current = current->next;
    }

    d = max_distance;

    current = context.coordinates->first;
    while (current) {
        y_perspective = (normedValue(current->data.y,2) * d) / (normedValue(current->data.x,1) + d);
        z_perspective = (normedValue(current->data.z,3) * d) / (normedValue(current->data.x,1) + d);
        QGraphicsEllipseItem *dataMarker = new QGraphicsEllipseItem(0, 0, context.cellSize/4, context.cellSize/4);
        dataMarker->setBrush(Qt::red);
        dataMarker->setPos(y_perspective*context.cellSize - context.cellSize/8, -z_perspective*context.cellSize - context.cellSize/8);
        scene->addItem(dataMarker);

        if (current != context.coordinates->first) {
            scene->addLine(y_perspective*context.cellSize, -z_perspective*context.cellSize, prevY * context.cellSize, -prevZ * context.cellSize, QPen(Qt::red));
        }

        prevY = y_perspective;
        prevZ = z_perspective;
        current = current->next;
    }
}

double MainWindow::normedValue(double value, int param) {
    return context.normalizationFrom + (value - findMin(param))/(findMax(param) - findMin(param))*(context.normalizationTo - context.normalizationFrom);
}

/*
//слишком много линий
void MainWindow::drawModel(QGraphicsScene *scene) {
    Node* current = context.coordinates->first;

    double y_perspective, z_perspective;
    int x0 = 0, y0 = 0, z0 = 0;
    double d;
    double max_distance = 0;

    while (current) {
        double distance = sqrt(pow(current->data.x - x0, 2) + pow(current->data.y - y0, 2) + pow(current->data.z - z0, 2));
        if (distance > max_distance)
            max_distance = distance;
        current = current->next;
    }

    d = max_distance;

    current = context.coordinates->first;
    while (current) {
        y_perspective = (current->data.y * d) / (current->data.x + d);
        z_perspective = (current->data.z * d) / (current->data.x + d);
        QGraphicsEllipseItem *dataMarker = new QGraphicsEllipseItem(0, 0, context.cellSize/4, context.cellSize/4);
        dataMarker->setBrush(Qt::red);
        dataMarker->setPos(y_perspective*context.cellSize - context.cellSize/8, -z_perspective*context.cellSize - context.cellSize/8);
        scene->addItem(dataMarker);
        Node* secondPoint = current->next;
        while (secondPoint) {
            double y_perspectiveSecond = (secondPoint->data.y * d) / (secondPoint->data.x + d);
            double z_perspectiveSecond = (secondPoint->data.z * d) / (secondPoint->data.x + d);
            scene->addLine(y_perspective*context.cellSize, -z_perspective*context.cellSize, y_perspectiveSecond * context.cellSize, -z_perspectiveSecond * context.cellSize, QPen(Qt::red));
            secondPoint = secondPoint->next;
        }
        current = current->next;
    }
}
*/

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
    movementTimer->start(100);
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
    movementTimer->start(100);
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
    movementTimer->start(100);
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
    movementTimer->start(100);
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
    movementTimer->start(100);
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
    movementTimer->start(100);
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
    rotationTimer->start(100);
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
    rotationTimer->start(100);
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
    rotationTimer->start(100);
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
    rotationTimer->start(100);
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
    scalingTimer->start(100);
    AppParams param;

    param.direction = 2;
    doOperation(ChangeDirection,&context,&param);
}

void MainWindow::onScalingUpButtonReleased() {
    scalingTimer->stop();
}

void MainWindow::onScalingDownButtonPressed() {
    scalingTimer->start(100);
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

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);

    updateLabels();
}

void MainWindow::adaptScene(QGraphicsScene *scene) {

}

