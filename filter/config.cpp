#include "config.h"


Config::Config() {
    success = false;
    QFile* file = new QFile("../config.xml");
    if (file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        success = true;

        QXmlStreamReader xml(file);

        while (!xml.atEnd() && !xml.hasError()) {
            QXmlStreamReader::TokenType token = xml.readNext();

            if (token == QXmlStreamReader::StartElement) {

                if (xml.name() == QString("zones")) {
                    zones = xml.readElementText().toInt();
                    continue;
                }

               if (xml.name() == QString("name")) {
                    name = xml.readElementText();
                    continue;
                }

                for(int i =1; i<= zones; i++)
                    if (xml.name() == QString("p" +QString::number(i))) {
                        power[i-1] = xml.readElementText().toInt();
                        continue;
                    }
            }
    }   }
}

    int Config::getPower(int i) const {
        return power[i];
    };



    int Config::getZones() const {
        return zones;
    }

