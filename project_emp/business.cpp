#include "business.h"
#include <QPrinter>
#include <QTextDocument>
#include <QPainter>
#include <QFile>
#include <QFileInfo>
#include <QPrintDialog>

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

std::vector<databaseData> Business::SelectWithDates(QDate from, QDate to)
{
    return connector.makeReport(from, to);
}

bool Business::Insert(databaseData *data)
{
    if(!connector.insert(data)) return false;
     int id = connector.selectRow();
     connector.insertPosition(data, id);
}

bool Business::Update(databaseData *data)
{
    connector.Update(data);
}

/*!
 * Method Report
 * \param from a QDate represent starting date to report
 * \param to a QDate represent ending date to report
*/
void Business::Report(QDate from, QDate to)
{
   reportStruct r;
   int money =0;

   std::vector<databaseData> report = connector.makeReport(from, to);
    if(report.empty()) return;
    std::vector<int> months;
    for(int i =0; i < report.size(); i++)
    {
        months.push_back(CountOfMonth(from, to, report.at(i).getDateFrom(), report.at(i).getDateTo()));
        money = money + (months.at(i)*report.at(i).getSalary());
    }
    r.from = from;
    r.to = to;
    r.money = money;

    CreatePdf(report,months,r);
}

/**
 * @brief Business::CountOfMonth
 * @param from
 * @param to
 * @param startDate
 * @param endDate
 * @return int counts ot months
 * function calculate number of months that employers wort at the company
 */
int Business::CountOfMonth(QDate from, QDate to, QDate startDate, QDate endDate)
{
    QDate d1;
    QDate d2;
    if(startDate <= from) d1 = from;
    else d1 = startDate;
    if(endDate >= to) d2 = to;
    else d2 = endDate;

    int months = (d2.year() - d1.year())*12 + d2.month() - d1.month();

    return months;
}

/**
 * @brief Business::CreatePdf
 * @param dat vector with data about employyes
 * @param months vector with correct months
 * @param r nessesery information that should be print on report
 */
void Business::CreatePdf(std::vector<databaseData> dat, std::vector <int> months, reportStruct r)
{
    QString fileName = "exportpdf";
       if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

       QPrinter printer(QPrinter::PrinterResolution);
       printer.setOutputFormat(QPrinter::PdfFormat);
       printer.setPaperSize(QPrinter::A4);
       printer.setOutputFileName(fileName);

       QPainter painter;
       painter.begin(&printer);

       QFont font;
       font.setBold(true);
       font.setPixelSize(30);
       painter.setFont(font);
       painter.drawText(250,20,"Report");

       font.setBold(false);
       font.setPixelSize(10);
       painter.setFont(font);

       painter.drawText(50,60,"report from: \t\t"+r.from.toString("dd.MM.yyyy"));
       painter.drawText(50,70,"report to:  \t\t"+r.to.toString("dd.MM.yyyy"));
       painter.drawText(50,80,"spent money: \t"+QString::number(r.money) + "€");

       painter.drawText(50,140,"First Name \t\t Last Name \t\t Start date \t End date \t Salary \t months");
       painter.drawLine(0,141,1000,141);

       for(int i =0; i<dat.size(); i++)
       {
            painter.drawText(50,((i+15)*10),dat.at(i).getFirstName() +
                             "\t\t" +dat.at(i).getLastName() +
                             "\t\t" + dat.at(i).getDateFrom().toString("dd.MM.yyyy") +
                             "\t" + dat.at(i).getDateTo().toString("dd.MM.yyyy") +
                             "\t" + QString::number(dat.at(i).getSalary()) +
                             "\t" + QString::number(months.at(i)));
       }
       QPrintDialog printDialog(&printer);

       if (printDialog.exec() == QDialog::Accepted) {
           // print ...
       }
}
