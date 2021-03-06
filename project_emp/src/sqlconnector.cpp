#include "sqlconnector.h"
#include "databasedata.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <vector>

using namespace std;


sqlConnector::sqlConnector()
{

}

sqlConnector::~sqlConnector()
{

}

bool sqlConnector::connect(QString usr, QString pass)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName(usr);
    db.setPassword(pass);
    db.setDatabaseName("employee_schema");

    if(db.open())
    {
        qDebug() << "connected " << db.hostName();
    }else{
        qDebug() << "Connection FAILED.";

        return false;
    }
    return true;
}

bool sqlConnector::insert(databaseData* dat)
{
    QSqlQuery query;
    query.prepare("insert into person (fname, lname) values (:fname,:lname);");
    query.bindValue(":lname",dat->getLastName());
    query.bindValue(":fname",dat->getFirstName());
    if(!query.exec()) return false;
       else
    {
       return true;
    }
}

bool sqlConnector::insertPosition(databaseData *dat, int id)
{
    QSqlQuery query;
    query.prepare("insert into position (id_person, date_from, date_to, salary)\
                   values(:id,:from,:to,:sal);");
    query.bindValue(":id",id);
    query.bindValue(":from",dat->getDateFrom());
    query.bindValue(":to",dat->getDateTo());
    query.bindValue(":sal",dat->getSalary());
    if(!query.exec()) return false;
       else return true;
}



vector<databaseData> sqlConnector::selectAll()
{
    QSqlQuery query;
    recdata.clear();
//    query.prepare("select* from person;");
    query.prepare("select p.fname, p.lname, p.id_person, s.date_from, s.date_to, s.salary from person  p LEFT JOIN position s USING(id_person)");
    query.exec();
    while(query.next()) {   //get all data about employees
            databaseData dat;
            dat.setFirstName(query.value(0).toString());
            dat.setLastName(query.value(1).toString());
            dat.setId(query.value(2).toInt());
            dat.setDateFrom(query.value(3).toDate());
            dat.setDateTo(query.value(4).toDate());
            dat.setSalary(query.value(5).toInt());
            recdata.push_back(dat);
        }
    return recdata;
}

int sqlConnector::selectRow()
{
    QSqlQuery query;
    int id = 0;
    query.prepare("select max(id_person) from person;");
    query.exec();
    while(query.next()) {//get id
            id = query.value(0).toInt();
    }
    return id;
}

bool sqlConnector::Update(databaseData *dat)
{
    QSqlQuery query;
    query.prepare("update person set fname= :fname, lname = :lname where id_person = :id;");
    query.bindValue(":fname",dat->getFirstName());
    query.bindValue(":lname",dat->getLastName());
    query.bindValue(":id",dat->getId());
    if(!query.exec()) return false;
       else
    {
        addEndDate(dat);
        return true;
    }
}

/**
 * @brief sqlConnector::addEndDate
 * @param dat
 * @return
 * add date to database when eployee leaving company
 */
bool sqlConnector::addEndDate(databaseData *dat)
{
    QSqlQuery query;
    query.prepare("update position set date_to = :to  where id_person = :id and date_from = :from;");
    query.bindValue(":to",dat->getDateTo());
    query.bindValue(":from",dat->getDateFrom());
    query.bindValue(":id",dat->getId());
    if(!query.exec()) return false;
       else return true;
}

bool sqlConnector::proLongContranct(databaseData *dat)
{
    QSqlQuery query;
    query.prepare("insert into postition values (:from, :to, :sal)  where id_person = :id;");
    query.bindValue(":to",dat->getDateTo());
    query.bindValue(":from",dat->getDateFrom());
    query.bindValue(":sal",dat->getSalary());
    query.bindValue(":id",dat->getId());
    if(!query.exec()) return false;
       else return true;
}

vector<databaseData> sqlConnector::makeReport(QDate from, QDate to)
{
    QSqlQuery query;
    recdata.clear();
    query.prepare("select p.fname, p.lname, p.id_person, s.date_from, s.date_to, s.salary from person  p JOIN position s USING(id_person) where (s.date_from < :to) AND (s.date_to > :from)");
    query.bindValue(":from",from);
    query.bindValue(":to",to);
    query.exec();
    while(query.next()) {
            databaseData dat;
            dat.setFirstName(query.value(0).toString());
            dat.setLastName(query.value(1).toString());
            dat.setId(query.value(2).toInt());
            dat.setDateFrom(query.value(3).toDate());
            dat.setDateTo(query.value(4).toDate());
            dat.setSalary(query.value(5).toInt());
            recdata.push_back(dat);
        }
    return recdata;

}



