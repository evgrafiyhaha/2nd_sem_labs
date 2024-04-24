#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <string>
#include <QTableView>
#include <QStandardItemModel>
#include <QGraphicsTextItem>
#include <string.h>
#include "appcontext.h"
#include "entrypoint.h"
#include "list.h"
#include "errors.h"
#include <QResizeEvent>

#define NO_ERRORS "No errors. yet"
#define COLUMN_ERROR "Insufficient column index"
#define REGION_ERROR "Insufficient region name"
#define FILE_NOT_CHOSEN_ERROR "File was not selected"
#define ZERO_ROWS_ERROR "There is no such region"
#define FILE_ERROR "File could not be opened"
#define EMPTY_TABLE_ERROR "Table is empty. Nothing to calculate"
#define ALLOCATION_ERROR "Memory could not be allocated"

#define OY_LENGTH 15
#define SPACER 4
#define BIG_NUM_FOR_COMP 10000
#define OY_NUMBER_OF_POINTS 10

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
    void on_calculateMetricsButton_clicked();

    void setTable();
    void setRow(Node* current,int row);
    void setFullTable(Node* current);
    void setRegionTable(Node* current);

    void setGraphic();
    void drawOY(QGraphicsScene *scene, int OYxValue, int OXyValue);
    void drawOXAndGraphic(QGraphicsScene *scene, int OYxValue, int OXyValue);
    double getField(Node* p, int column);
    void resizeEvent(QResizeEvent* event) override;
    Node* drawGraphic(QGraphicsScene *scene, Node* current, int year, int x, int OXyValue, int* isFirst, double* prevX, double* prevY);
    double findScale();
    int findMinYear();
    int findMaxYear();

    void updateLabels();
    void errorCodeHandler();

private:
    Ui::MainWindow *ui;
    AppContext context;
};
#endif // MAINWINDOW_H
