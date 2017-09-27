#include "logindialog.h"
#include "ui_logindialog.h"
#include "mainwindow.h"
#include "business.h"
#include <QMessageBox>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    LoginDialog::setFixedSize(300,116);
    ui->lineEditPass->setEchoMode(QLineEdit::Password);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    QString login = ui->lineEditLogin->text();
    QString pass = ui->lineEditPass->text();
    if((login.isEmpty()) || (pass.isEmpty()))
    {
        QMessageBox::warning(this,"Error","Set login and password");
    }else{
        if(!businesLogin.Connect(login,pass)){
             QMessageBox::warning(this,"Error","Incorrect login or password");
             return;
        }
        QDialog::accept();
    }
}
