#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QClipboard>
#include "appcontext.h"
#include "entrypoint.h"
#include <string.h>

#define ERROR_CODE_0_TEXT "No errors found. yet"
#define ERROR_CODE_1_TEXT "Your number is too long and has unsuitable signs"
#define ERROR_CODE_2_TEXT "Your number is too long"
#define ERROR_CODE_3_TEXT "Your number has unsuitable signs"

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

private:
    Ui::MainWindow *ui;
    AppContext context;

    void onTranslateClicked();
    void onBufferButtonClicked();
    void updateLabels();
    void errorCodeHandler(AppContext* context);
    void onSwitchButtonClicked();
};
#endif // MAINWINDOW_H
