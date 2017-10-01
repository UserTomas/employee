#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "business.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginDialog *ui;
    Business businesLogin;
};

#endif // LOGINDIALOG_H
