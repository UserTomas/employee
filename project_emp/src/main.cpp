#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::cout << "hello";

        MainWindow w;
        w.show();

    return a.exec();
}
