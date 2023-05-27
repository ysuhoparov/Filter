
#include "mainwindow.h"

#include <QApplication>
#include "channel.h"
uint Channel::status =127;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
