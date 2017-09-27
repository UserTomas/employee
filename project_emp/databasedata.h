#ifndef DATABASEDATA_H
#define DATABASEDATA_H

#include <QString>
#include <QDate>

class databaseData
{
public:
    databaseData();
    ~databaseData();
    void setFirstName(QString name);
    void setLastName(QString name);
    void setId(int id);
    void setDateFrom(QDate date);
    void setDateTo(QDate data);
    void setSalary(int value);
    int getId();
    int getSalary();
    QString getFirstName();
    QString getLastName();
    QDate getDateFrom();
    QDate getDateTo();


private:
    int mId;
    int mSalary;
    QString mFirstName;
    QString mLastName;
    QDate dateFrom;
    QDate dateTo;


};

#endif // DATABASEDATA_H
