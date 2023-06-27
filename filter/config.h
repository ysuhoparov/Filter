#ifndef CONFIG_H
#define CONFIG_H

#include <QFile>
#include <QMainWindow>
#include <QXmlStreamReader>

class Config
{
    int zones;
    int power[8];

public:
    Config();
    int getZones() const ;
    int getPower(int) const ;
    QString name;
    bool success;

};

#endif // CONFIG_H
