#ifndef database_H
#define database_H
#include "vector.h"
#include <QTableWidget>
#include <QMessageBox>
#include <algorithm>
#include <QDebug>
#include <QObject>
#include <QFileDialog>
#include "adddialog.h"
#include <knigi.h>
class database : public QObject
{
    Q_OBJECT
public:
    explicit database(QObject *parent = 0);
    ~database();
    void find(QString s,QTableWidget *t);
    void saveToFile(const QString &fileName);
    void loadFromFile(const QString &fileName);
    void add(const Kniga& Kniga_);
    void change(int n);
    void del(int numRow);
    void addtotable(QTableWidget *t);
    void merge(const QString &fileName);
    void clear();
private:
    vector<Kniga> v;
    bool saved;
signals:
public slots:
    bool isSaved();
};
#endif // database_H
