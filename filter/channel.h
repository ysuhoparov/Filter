
#ifndef CHANNEL_H
#define CHANNEL_H

#include "netinfo.h"

#include <QString>
#include <QObject>
#include <QThread>

class Channel:public QObject
{
    Q_OBJECT
public:
    Channel();
    ~Channel();
    NetInfo controllerData;
   static uint status;

protected:
    unsigned char *udemo;

 public slots:
    void network();

signals:
    void send(NetInfo);

};

#endif // CHANNEL_H
