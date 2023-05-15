#include "database.h"
database::database(QObject *parent):
    QObject(parent),saved(true){}
database::~database(){}
void database::add(const Kniga &Kniga_)
{
    v.push_back(Kniga_);
    saved=false;
}
void database::change(int n)
{
    AddDialog myDialog(0,v[n]);
    int result = myDialog.exec();
    if (QDialog::Accepted == result)
    {
        v[n]=myDialog.getdata();
        saved=false;
    }
}
void database::del(int numRow)
{
    saved=false;
    v.del(numRow);
}
void database::saveToFile(const QString &fileName)
{
    if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                return;
            }
            else
            {
            QString str("");
               typename vector<Kniga>::iterator iter;
               for(iter=v.begin(); iter!=v.end();++iter)
               {
                   str.append(iter->avtor);
                   str.append("|");
                   str.append(iter->nazvanie);
                   str.append("|");
                   str.append(iter->izdatestvo);
                   str.append("|");
                   str.append(iter->janr);
                   str.append("|");
                   str.append(iter->opisanie);
                   str.append("|");
                   str.append(iter->godizdan);
                   str.append("\n");
               }
                   QByteArray ar;
                   ar.append(str);
                   file.write(ar);
                }
                  file.close();
                  saved=true;
              }
}
 void database::loadFromFile(const QString &fileName)
 {
     if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                //QMessageBox::information(this, tr("Unable to open file"),
                   // file.errorString());
                return;
            }
            QTextStream stream(&file);
                QString str;
                QStringList fields;
                Kniga tmp;
                while(!stream.atEnd())
                {
                    str=stream.readLine();
                    str=str.simplified();
                    fields=str.split("|");
                    tmp.avtor=fields[0];
                    tmp.nazvanie=fields[1];
                    tmp.izdatestvo=fields[2];
                    tmp.janr=fields[3];
                    tmp.opisanie=fields[4];
                    tmp.godizdan=fields[5];
                    add(tmp);
                }
                file.close();
                saved=true;
     }
 }
bool database::isSaved()
{
    return saved;
}
void database::clear()
{
    saved=false;
    v.clear();
}
void database::addtotable(QTableWidget *table)
{
    typename vector<Kniga>::iterator iter=v.begin();
    for (iter=v.begin();iter!=v.end();++iter)
    {
        table->setRowCount(table->rowCount()+1);
        table->setItem(table->rowCount()-1,0,new QTableWidgetItem(iter->avtor));
        table->setItem(table->rowCount()-1,1,new QTableWidgetItem(iter->nazvanie));
        table->setItem(table->rowCount()-1,2,new QTableWidgetItem(iter->izdatestvo));
        table->setItem(table->rowCount()-1,3,new QTableWidgetItem(iter->janr));
        table->setItem(table->rowCount()-1,4,new QTableWidgetItem(iter->opisanie));
        table->setItem(table->rowCount()-1,5,new QTableWidgetItem(iter->godizdan));
    }
}
void database::merge(const QString &fileName)
{
    if (fileName.isEmpty())
           return;
       else {
           QFile file(fileName);
           if (!file.open(QIODevice::ReadOnly)) {
               return;
           }
           QTextStream stream(&file);
               QString str;
               QStringList fields;
               Kniga tmp;
               while(!stream.atEnd())
               {
                   str=stream.readLine();
                   str=str.simplified();
                   fields=str.split("|");
                   tmp.avtor=fields[0];
                   tmp.nazvanie=fields[1];
                   tmp.izdatestvo=fields[2];
                   tmp.janr=fields[3];
                   tmp.opisanie=fields[4];
                   tmp.godizdan=fields[5];
                   add(tmp);
               }
               file.close();
               saved=false;
    }
}
void database::find(QString s, QTableWidget *table)
{
    typename vector<Kniga>::iterator iter;
    for (iter=v.begin();iter!=v.end();++iter)
    {
        if (    iter->avtor.contains(s)||
                iter->nazvanie.contains(s)||
                iter->izdatestvo.contains(s)||
                iter->janr.contains(s)||
                iter->opisanie.contains(s)||
                iter->godizdan.contains(s))
        {

            table->setRowCount(table->rowCount()+1);
            table->setItem(table->rowCount()-1,0,new QTableWidgetItem(iter->avtor));
            table->setItem(table->rowCount()-1,1,new QTableWidgetItem(iter->nazvanie));
            table->setItem(table->rowCount()-1,2,new QTableWidgetItem(iter->izdatestvo));
            table->setItem(table->rowCount()-1,3,new QTableWidgetItem(iter->janr));
            table->setItem(table->rowCount()-1,4,new QTableWidgetItem(iter->opisanie));
            table->setItem(table->rowCount()-1,5,new QTableWidgetItem(iter->godizdan));
        }
    }
}
