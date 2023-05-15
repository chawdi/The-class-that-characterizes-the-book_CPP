#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QTableView>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    base_=new database();
    ui->toolBar->addWidget(ui->search);
    ui->toolBar->setVisible(false);
    ui->toolBar->addAction(ui->actionClosefind);
    connect(ui->findline,SIGNAL(textChanged(QString)),this,SLOT(onfindlinechanged(QString)));
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionNew_triggered()
{
    if (!base_->isSaved())
    {
        QMessageBox msgBox;
        msgBox.setText("Do you want to save your changes?");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();
        if (ret==QMessageBox::Yes)
        on_actionSave_triggered();
    }
    setWindowTitle("new base");
    base_->clear();
    tablereset();
}
void MainWindow::on_actionAdd_triggered()
{
    AddDialog myDialog;
    int result = myDialog.exec();
    if (QDialog::Accepted == result)
    {
        base_->add( myDialog.getdata());
        tablereset();
        base_->addtotable(ui->tableWidget);
    }
    ui->statusBar->showMessage("Entry added");
}
void MainWindow::on_actionChange_triggered()
{
  if (!ui->tableWidget->selectedItems().isEmpty())
  base_->change(ui->tableWidget->selectedItems().back()->row());
  tablereset();
  base_->addtotable(ui->tableWidget);
}
void MainWindow::on_actionDelete_triggered()
{
    QMessageBox msgBox;

    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("Do you want to delete an entry?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if (ret==QMessageBox::Ok)
    if (!ui->tableWidget->selectedItems().isEmpty())
    {
      int numRow=ui->tableWidget->selectedItems().last()->row();
      ui->tableWidget->removeRow(numRow);
      base_->del(numRow);
    }
    ui->statusBar->showMessage("Entry deleted");
}
void MainWindow::on_actionExit_triggered()
{
    close();
}
void MainWindow::on_actionSave_triggered()
{
    QString fileName;
    if (windowTitle()=="new base")
    {
    fileName = QFileDialog::getSaveFileName(this,
           tr("Open Data Base"), "new base.tvbd",
           tr("Base (*.tvbd);;All Files (*)"));
        setWindowTitle(fileName);
    }
    else
        fileName=windowTitle();
    base_->saveToFile(fileName);
    ui->statusBar->showMessage("Saved");
}
void MainWindow::on_actionOpen_triggered()
{
    if (!base_->isSaved())
    {
        QMessageBox msgBox;

        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();
        if (ret==QMessageBox::Yes)
        on_actionSave_triggered();
    }
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Data Base"), "",
            tr("Base (*.tvbd);;All Files (*)"));
    setWindowTitle(fileName);
    base_->clear();
    tablereset();
    base_->loadFromFile(fileName);
    base_->addtotable(ui->tableWidget);
    ui->statusBar->showMessage("Base is open");
}
void MainWindow::tablereset()
{

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    QStringList s;
    s.append("Author");
    s.append("Name");
    s.append("publishing house");
    s.append("Genre");
    s.append("Description");
    s.append("The year of publishing");
    ui->tableWidget->setHorizontalHeaderLabels(s);
}
void MainWindow::on_actionSaveAs_triggered()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,
           tr("Open Data Base"), "new base.tvbd",
           tr("Base (*.tvbd);;All Files (*)"));
        setWindowTitle(fileName);
    base_->saveToFile(fileName);
}
void MainWindow::on_actionMerge_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Data Base"), "",
            tr("Base (*.tvbd);;All Files (*)"));
    if (fileName!=windowTitle())
    {
    base_->merge(fileName);
    tablereset();
    base_->addtotable(ui->tableWidget);
    }
    ui->statusBar->showMessage("Bases merged");
}
void MainWindow::on_actionSearch_triggered()
{
    ui->toolBar->setVisible(true);
    ui->findline->setFocus();
}
void MainWindow::on_actionClosefind_triggered()
{
    ui->toolBar->setVisible(false);
    ui->statusBar->showMessage(" ");
}
void MainWindow::onfindlinechanged(QString str)
{
    tablereset();
    base_->find(str,ui->tableWidget);
    ui->statusBar->showMessage("Found "+QString::number(ui->tableWidget->rowCount())+" records" );
}
void MainWindow::closeEvent(QCloseEvent *)
{
    if (!base_->isSaved())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();
        if (ret==QMessageBox::Yes)
        on_actionSave_triggered();
    }
}
void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"About the program","Coursework in the discipline of OOP\n""Subject: Database characterizing the book\n""Option 6\n"
     "Performed by a student of the group IKPI-85 \n" "Kuzmin Artemy\n" "St. Petersburg\n" "2018");
}
