#include "databasedata.h"

databaseData::databaseData()
{

    mFirstName = "";
    mLastName = "";
    mId = 0;
    mSalary = 0;

}

databaseData::~databaseData()
{

}

void databaseData::setFirstName(QString name)
{
    mFirstName = name;

}

void databaseData::setLastName(QString name)
{
    mLastName = name;
}

int databaseData::getId()
{
    return mId;
}

QString databaseData::getFirstName()
{
    return mFirstName;
}

QString databaseData::getLastName()
{
    return mLastName;
}

void databaseData::setId(int id)
{
    mId = id;
}

void databaseData::setDateFrom(QDate date)
{
    dateFrom = date;
}

QDate databaseData::getDateFrom()
{
    return dateFrom;
}

void databaseData::setDateTo(QDate data)
{
    dateTo = data;
}

void databaseData::setSalary(int value)
{
    mSalary = value;
}

int databaseData::getSalary()
{
    return mSalary;
}

QDate databaseData::getDateTo()
{
    return dateTo;
}
