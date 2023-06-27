#ifndef REPORT_H
#define REPORT_H

#include <QObject>

#include <QSqlQueryModel>

class Report : public QObject
{
    Q_OBJECT
public:
    explicit Report(QObject *parent = nullptr);

    static void parameters();
    static void service();


};

#endif // REPORT_H
