#include "insertdialog.h"
#include "ui_insertdialog.h"
#include <QDebug>
#include <QDate>
#include <QMessageBox>


InsertDialog::InsertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertDialog)
{
    ui->setupUi(this);
    editing = false;
    data = new databaseData();
    ui->dateEditFrom->setDate(QDate::currentDate());
    ui->dateEditTo->setDate(QDate::currentDate());
    ui->lineEditSalary->setInputMask("0000000");

}

InsertDialog::InsertDialog(bool edit, QString fname, QString lname, int id, int sal, QString dateFrom, QString dateTo,
                           QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertDialog)
{
    ui->setupUi(this);
    ui->lineEditFName->setText(fname);
    ui->lineEditLName->setText(lname);
    ui->lineEditSalary->setText(QString::number(sal));
    ui->dateEditFrom->setDate(QDate::fromString(dateFrom,"dd.MM.yyyy"));
    ui->dateEditTo->setDate(QDate::fromString(dateTo,"dd.MM.yyyy"));
    editing = edit;
    data = new databaseData();
    data->setId(id);
    ui->lineEditSalary->setDisabled(true);
    ui->dateEditFrom->setDisabled(true);
    ui->checkBoxUseDateTo->setChecked(true);
}


InsertDialog::~InsertDialog()
{
    delete ui;
    delete data;
    delete con;
}

void InsertDialog::on_btnCancel_clicked()
{
    QWidget::close();
}



void InsertDialog::on_btnOk_clicked()
{
    if(ui->lineEditFName->text().isEmpty() || ui->lineEditLName->text().isEmpty()||
            ui->lineEditSalary->text().isEmpty())
    {
        QMessageBox::warning(this,"Error","Missing values");
        return;
    }
    if(ui->checkBoxUseDateTo->isChecked()) data->setDateTo(ui->dateEditTo->date());
    data->setFirstName(ui->lineEditFName->text());
    data->setLastName(ui->lineEditLName->text());
    data->setDateFrom(ui->dateEditFrom->date());
    data->setSalary(ui->lineEditSalary->text().toInt());
    if(!editing){
        busines.Insert(data);
        this->close();
    }else{
        busines.Update(data);
        this->close();
    }
}
