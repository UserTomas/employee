#include "business.h"

Business::Business()
{

}

Business::~Business()
{

}

bool Business::Connect(QString usr, QString pass)
{
    if(!connector.connect(usr,pass)) return false;
    return true;
}

std::vector<databaseData> Business::SelectAll()
{
    return connector.selectAll();
}

bool Business::Insert(databaseData *data)
{
    connector.insert(data);
}

bool Business::Update(databaseData *data)
{
    connector.Update(data);
}

