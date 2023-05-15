#include "adddialog.h"
#include "ui_adddialog.h"
AddDialog::AddDialog(QWidget *parent,const Kniga& Kniga_) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    ui->avtorLine->setText(Kniga_.avtor);
    ui->nazvanieLine->setText(Kniga_.nazvanie);
    ui->izdatelstvoLine->setText(Kniga_.izdatestvo);
    ui->janrLine->setText(Kniga_.janr);
    ui->opisanieLine->setText(Kniga_.opisanie);
    ui->godizdanLine->setText(Kniga_.godizdan);
}
AddDialog::~AddDialog()
{
    delete ui;
}
Kniga AddDialog::getdata()
{
    Kniga Kniga_;
    Kniga_.avtor=ui->avtorLine->text();
    Kniga_.nazvanie=ui->nazvanieLine->text();
    Kniga_.izdatestvo=ui->izdatelstvoLine->text();
    Kniga_.janr=ui->janrLine->text();
    Kniga_.opisanie=ui->opisanieLine->text();
    Kniga_.godizdan=ui->godizdanLine->text();
    return Kniga_;
}
