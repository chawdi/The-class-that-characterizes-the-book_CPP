#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "adddialog.h"
#include "database.h"
#include <QMainWindow>
#include <QSpacerItem>
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void tablereset();
private slots:
    void onfindlinechanged(QString);
    void on_actionNew_triggered();
    void on_actionAdd_triggered();
    void on_actionChange_triggered();
    void on_actionDelete_triggered();
    void on_actionExit_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionSaveAs_triggered();
    void on_actionMerge_triggered();
    void on_actionSearch_triggered();
    void on_actionClosefind_triggered();
    void closeEvent(QCloseEvent *);
    void on_actionAbout_triggered();
private:
    Ui::MainWindow *ui;
    database *base_;
};
#endif // MAINWINDOW_H
