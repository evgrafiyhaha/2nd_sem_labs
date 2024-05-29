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
#define TIMER_TIME 30
#define CELL_SIZE 20


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
    void onSelectFileButtonClicked();
    void onLoadDataButtonClicked();

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



    void movementXForwardTimerTimeout();
    void movementXBackTimerTimeout();

    void movementZUpTimerTimeout();
    void movementZDownTimerTimeout();

    void movementYRightTimerTimeout();
    void movementYLeftTimerTimeout();

    void rotationZUpTimerTimeout();
    void rotationZDownTimerTimeout();

    void rotationYLeftTimeout();
    void rotationYRightTimerTimeout();

    void scalingUpTimerTimeout();
    void scalingDownTimerTimeout();

    void showModel();
    void drawModel(QGraphicsScene *scene);
    void drawShowcasePoint(QGraphicsScene *scene, double x0);

    void updateLabels();
    void errorCodeHandler();
    double findMax(Coordinates param);
    double findMin(Coordinates param);
    Point findPrev(List* prevPointsList, int counter);

private:
    Ui::MainWindow *ui;

    QTimer *movementXForwardTimer;
    QTimer *movementXBackTimer;

    QTimer *movementZUpTimer;
    QTimer *movementZDownTimer;

    QTimer *movementYRightTimer;
    QTimer *movementYLeftTimer;

    QTimer *rotationZUpTimer;
    QTimer *rotationZDownTimer;
    QTimer *rotationYLeftTimer;
    QTimer *rotationYRightTimer;

    QTimer *scalingUpTimer;
    QTimer *scalingDownTimer;

    AppContext context;
};
#endif // MAINWINDOW_H
