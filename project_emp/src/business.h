#ifndef BUSINESS_H
#define BUSINESS_H

#include "sqlconnector.h"
#include "databasedata.h"

class Business
{
public:

    struct reportStruct {
        QDate from;
        QDate to;
        int money;
    };

    sqlConnector connector;

    Business();
    ~Business();
    bool Connect(QString usr, QString pass);
    std::vector<databaseData> SelectAll();
    std::vector<databaseData> SelectWithDates(QDate from, QDate to);
    bool Insert(databaseData *data);
    bool Update(databaseData *data);
    void Report(QDate from, QDate to);
    void CreatePdf(std::vector<databaseData> dat, std::vector<int> months,reportStruct r);
    int CountOfMonth(QDate from, QDate to, QDate startDate, QDate endDate);


};

#endif // BUSINESS_H
