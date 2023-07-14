#include "report.h"
#include "qboxlayout.h"
#include "qtableview.h"
#include "qwidget.h"

Report::Report(QObject *parent) : QObject{parent} {}


void Report::parameters()
{
    QSqlQueryModel * model = new QSqlQueryModel;

    model->setQuery("select timerec, field1%256 as U_field1, field1/256%256 as I_field1, "
                    "field2 % 256 as U_2, field2 / 256 % 256 as I_2, "
                    "field3 % 256 as U_3, field3 / 256 % 256 as I_3, "
                    "field4 % 256 as U_4, field4 / 256 % 256 as I_4 "
                    "from history order by id desc LIMIT 25");

    model->setHeaderData(0, Qt::Horizontal, "Время");

    QWidget* tableWindow = new QWidget;
    tableWindow->resize(1024,640);
    QHBoxLayout* tableLay = new QHBoxLayout(tableWindow);
    tableWindow->setWindowTitle("Параметры питания полей фильтра");

    QTableView* tableView = new QTableView;
    tableView->setModel(model);
    tableView->resizeColumnToContents(0);
    tableLay->addWidget(tableView);

    tableWindow->show();
}

void Report::parameters(const QDateTime& reportTime)
{
    QSqlQuery query;
    query.prepare("select timerec, field1%256 as U_field1, field1/256%256 as I_field1, "
                  "field2 % 256 as U_2, field2 / 256 % 256 as I_2, "
                  "field3 % 256 as U_3, field3 / 256 % 256 as I_3, "
                  "field4 % 256 as U_4, field4 / 256 % 256 as I_4 "
                  "from history where timerec <= :rtime order by id desc LIMIT 25");
    query.bindValue(":rtime", reportTime);
    query.exec();

    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "Время");

    QWidget* tableWindow = new QWidget;
    tableWindow->resize(1024,640);
    QHBoxLayout* tableLay = new QHBoxLayout(tableWindow);
    tableWindow->setWindowTitle("Параметры питания полей фильтра");

    QTableView* tableView = new QTableView;
    tableView->setModel(model);
    tableView->resizeColumnToContents(0);
    tableLay->addWidget(tableView);

    tableWindow->show();
}



void Report::service()
{
    QSqlQueryModel * model = new QSqlQueryModel;

    model->setQuery("select field, date, equipment, manufacturer, value from service");
    model->setHeaderData(0, Qt::Horizontal, "Поле");
    model->setHeaderData(1, Qt::Horizontal, "Дата замены");
    model->setHeaderData(2, Qt::Horizontal, "Оборудование");
    model->setHeaderData(3, Qt::Horizontal, "Производитель");
    model->setHeaderData(4, Qt::Horizontal, "Характеристика");

    QWidget* tableWindow = new QWidget;
    tableWindow->resize(900,400);
    QHBoxLayout* tableLay = new QHBoxLayout(tableWindow);
    tableWindow->setWindowTitle("Ведомость технического обслуживания и ремонта");

    QTableView* tableView = new QTableView;
    tableView->setModel(model);
    tableView->resizeColumnsToContents();
    tableLay->addWidget(tableView);

    tableWindow->show();
}
