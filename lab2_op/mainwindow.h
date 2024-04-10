#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "appcontext.h"
#include "entrypoint.h"
#include <string.h>
#include "list.h"
#include <string>
#include <QTableView>
#include <QStandardItemModel>
#include "errors.h"

#define NO_ERRORS "No errors. yet"
#define COLUMN_ERROR "Insufficient column index"
#define REGION_ERROR "Insufficient region name"
#define FILE_NOT_CHOSEN_ERROR "File was not selected"
#define ZERO_ROWS_ERROR "There is no such region"
#define FILE_ERROR "File could not be opened"
#define EMPTY_TABLE_ERROR "Table is empty. Nothing to calculate"
#define ALLOCATION_ERROR "Memory could not be allocated"


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

    void updateLabels();
    void errorCodeHandler();

private:
    Ui::MainWindow *ui;
    AppContext context;
};
#endif // MAINWINDOW_H
