#ifndef ADDDIALOG_H
#define ADDDIALOG_H
#include <QDialog>
#include "database.h"
#include "knigi.h"
#include<QAbstractButton>
namespace Ui {
class AddDialog;
}
class AddDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddDialog(QWidget *parent = 0,
            const Kniga& kniga_=Kniga());
    ~AddDialog();
    Kniga getdata();
private:
    Ui::AddDialog *ui;
};
#endif // ADDDIALOG_H
