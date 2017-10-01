#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QtCore>
#include <QtGui>
#include <QDate>
#include <QTreeWidgetItem>
#include "sqlconnector.h"
#include "insertdialog.h"
#include "business.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void addRoot(QString name, QString description, int id, QDate datFrom, QDate datTo, int sal);
    void addChild(QTreeWidgetItem *parent, QString name, QString description);


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    sqlConnector connector;   //business

public slots:
    void openInsertDialog();
    void Active();

private slots:
    void on_pushButton_clicked();



    void on_update_clicked();

    void on_btnReport_clicked();

private:
    Ui::MainWindow *ui;
    InsertDialog *mInsertDialog;
    Business busines;
};

#endif // MAINWINDOW_H
