#ifndef REPORT_H
#define REPORT_H

#include <QObject>

#include <QDateTime>
#include <QSqlQueryModel>
#include <QSqlQuery>


class Report : public QObject
{
    Q_OBJECT
public:
    explicit Report(QObject *parent = nullptr);

    static void parameters();
    static void parameters(const QDateTime&);
    static void service();


};

#endif // REPORT_H
