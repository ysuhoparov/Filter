
#include "mainwindow.h"

#include <QApplication>
#include "channel.h"
uint Channel::status =15;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
  //  Channel::status[0] =1;
    w.show();
    return a.exec();
}
