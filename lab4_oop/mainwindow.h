#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QGraphicsTextItem>
#include <QButtonGroup>
#include <QRadioButton>

#include "facade.h"

#define NO_OPERATION_ERROR "Operation was not chosen."
#define NOT_CONVERTABLE_ERROR "Parameters can't be converted to double"

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
    void onSelectFileButtonClicked();
    void onDrawSceneButtonClicked();
    void OnDoOperationButtonClicked();

private:
    Ui::MainWindow *ui;
    Facade facade;
    QButtonGroup *buttonGroup;
};
#endif // MAINWINDOW_H
