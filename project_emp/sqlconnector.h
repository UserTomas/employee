#ifndef SQLCONNECTOR_H
#define SQLCONNECTOR_H

#include <QSqlQuery>
#include "databasedata.h"
#include <vector>
#include <QDate>

class sqlConnector
{

public:


    std::vector<databaseData> recdata;

    sqlConnector();
    ~sqlConnector();
    bool insert(databaseData *dat);
    std::vector<databaseData> selectAll();
    bool connect(QString usr, QString pass);
    bool Update(databaseData *dat);
    bool insertPosition(databaseData *dat, int id);
    bool addEndDate(databaseData *dat);
    bool proLongContranct(databaseData *dat);
    std::vector<databaseData> makeReport(QDate from, QDate to);
    int selectRow();
};

#endif // SQLCONNECTOR_H
