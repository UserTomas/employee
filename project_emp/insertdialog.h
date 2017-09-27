#ifndef INSERTDIALOG_H
#define INSERTDIALOG_H

#include <QDialog>
#include "databasedata.h"
#include "sqlconnector.h"
#include "business.h"

namespace Ui {
class InsertDialog;
}

class InsertDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsertDialog(QWidget *parent = 0);
    explicit InsertDialog(bool edit, QString fname, QString lname, int id, int sal, QString dateFrom, QString dateTo, QWidget *parent = 0);
    ~InsertDialog();

private slots:
    void on_btnCancel_clicked();


    void on_btnOk_clicked();

private:
    Ui::InsertDialog *ui;
    databaseData *data;
    sqlConnector *con;
    Business busines;
    bool editing;
};

#endif // INSERTDIALOG_H
