#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QGraphicsTextItem>
#include <QResizeEvent>
#include <QTimer>

#include "appcontext.h"
#include "entrypoint.h"
#include "list.h"
#include "errors.h"


#define BIG_NUM_FOR_COMP 10000
#define TIMER_TIME 100


#define NO_ERRORS "No errors. yet"
#define FILE_NOT_CHOSEN_ERROR "File was not selected"
#define FILE_ERROR "File could not be opened"
#define ALLOCATION_ERROR "Memory could not be allocated"
#define EMPTY_LIST_ERROR "List of coordinates is empty"
#define NORMAL_ERROR "Incorrect normalization values"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_selectFileButton_clicked();
    void on_loadDataButton_clicked();

    void onMoveUpButtonPressed();
    void onMoveUpButtonReleased();

    void onMoveDownButtonPressed();
    void onMoveDownButtonReleased();

    void onMoveLeftButtonPressed();
    void onMoveLeftButtonReleased();

    void onMoveRightButtonPressed();
    void onMoveRightButtonReleased();

    void onMoveBackButtonPressed();
    void onMoveBackButtonReleased();

    void onMoveForwardButtonPressed();
    void onMoveForwardButtonReleased();

    void onRotateUpButtonPressed();
    void onRotateUpButtonReleased();

    void onRotateDownButtonPressed();
    void onRotateDownButtonReleased();

    void onRotateLeftButtonPressed();
    void onRotateLeftButtonReleased();

    void onRotateRightButtonPressed();
    void onRotateRightButtonReleased();

    void onScalingUpButtonPressed();
    void onScalingUpButtonReleased();

    void onScalingDownButtonPressed();
    void onScalingDownButtonReleased();

    void onScalingTimeout();
    void onRotationTimeout();
    void onMovementTimeout();

    void showModel();
    void drawModel(QGraphicsScene *scene);

    void updateLabels();
    void errorCodeHandler();
    double findMax(coordinates param);
    double findMin(coordinates param);
    Point findPrev(List* prevPointsList, int counter);

private:
    Ui::MainWindow *ui;
    QTimer *movementTimer;
    QTimer *rotationTimer;
    QTimer *scalingTimer;
    AppContext context;
};
#endif // MAINWINDOW_H
