#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "sqlconnector.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QDesktopWidget>
#include <QPrinter>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth, width;
    int screenHeight, height;
    int x, y;
    QSize windowSize;

    screenWidth = desktop->width(); // get width of screen
    screenHeight = desktop->height(); // get height of screen

    windowSize = size(); // size of our application window
    width = windowSize.width();
    height = windowSize.height();

    // little computations
    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;
    y -= 50;

    // move window to desired coordinates
    move ( x, y );

    ui->setupUi(this);
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->setHeaderLabels((QStringList)"First Name"<<"Last Name" << "ID" << "Date From" <<"Date To" << "Salary");
    this->setEnabled(false);

    LoginDialog *login = new LoginDialog(this);
    login->show();

    connect(ui->btnInsert,SIGNAL(clicked(bool)), this, SLOT(openInsertDialog()));
    connect(login, SIGNAL(accepted()),this, SLOT(Active()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openInsertDialog()
{
    mInsertDialog = new InsertDialog(this);
    mInsertDialog->show();
}

void MainWindow::on_pushButton_clicked()
{
    ui->treeWidget->clear();

    std::vector<databaseData>  data;
    data = busines.SelectAll();
    for(int i =0; i< data.size(); i++)
    {
        addRoot(data.at(i) .getFirstName(),data.at(i).getLastName(), data.at(i).getId(),
                data.at(i).getDateFrom(),data.at(i).getDateTo(),data.at(i).getSalary());
    }
    data.clear();
}

void MainWindow::addRoot(QString name, QString description, int id, QDate datFrom, QDate datTo, int sal)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0,name);
    itm->setText(1,description);
    itm->setText(2,QString::number(id));
    itm->setText(3,datFrom.toString("dd.MM.yyyy"));
    itm->setText(4,datTo.toString("dd.MM.yyyy"));
    itm->setText(5,QString::number(sal));
    ui->treeWidget->addTopLevelItem(itm);
}

void MainWindow::addChild(QTreeWidgetItem *parent, QString name, QString description)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0,name);
    itm->setText(1,description);
    parent->addChild(itm);
}

void MainWindow::on_update_clicked()
{
//    QStringList infos;
    if(!ui->treeWidget->currentItem())
    {
        QMessageBox::warning(this,"Error","No selected row");
    }
    else {
        QTreeWidgetItem *row = ui->treeWidget->currentItem();
        QString from = row->text(3);
        mInsertDialog = new InsertDialog(true, row->text(0),row->text(1), row->text(2).toInt(), row->text(5).toInt(),
                                        row->text(3), row->text(4), this);
        mInsertDialog->show();
    }
}

void MainWindow::Active()
{
    this->setEnabled(true);
}

void MainWindow::on_btnReport_clicked()
{

    QString fileName = "exportpdf";
       if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

       QPrinter printer(QPrinter::PrinterResolution);
       printer.setOutputFormat(QPrinter::PdfFormat);
       printer.setPaperSize(QPrinter::A4);
       printer.setOutputFileName(fileName);

//       QTextDocument doc;
//       doc.setHtml("<h1>Hello, World!</h1>\n<p>Lorem ipsum dolor sit amet, consectitur adipisci elit.</p>");
//       doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
//       doc.setHtml();
//       doc.print(&printer);

       QPainter painter;
       painter.begin(&printer);

         QTreeWidgetItem *row = ui->treeWidget->currentItem();

        painter.drawText(10,90,row->text(0));

}
