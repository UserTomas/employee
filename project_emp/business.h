#ifndef BUSINESS_H
#define BUSINESS_H

#include "sqlconnector.h"
#include "databasedata.h"

class Business
{
public:
    sqlConnector connector;

    Business();
    ~Business();
    bool Connect(QString usr, QString pass);
    std::vector<databaseData> SelectAll();
    bool Insert(databaseData *data);
    bool Update(databaseData *data);

};

#endif // BUSINESS_H
