#include "config.h"


Config::Config() {

    QFile* file = new QFile("../config.xml");
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {;
    }
    QXmlStreamReader xml(file);

    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartElement) {
            if (xml.name() == QString("zones")) {
                zones = xml.readElementText().toInt();
                continue;
            }

            for(int i =1; i<= zones; i++)
                if (xml.name() == QString("p" +QString::number(i))) {
                    power[i-1] = xml.readElementText().toInt();
                    continue;
                }
        }
    }
}

    int Config::getPower(int i) const {
        return power[i];
    };



    int Config::getZones() const {
        return zones;
    }




//    //int k=0;

//    QFile* file = new QFile("../config.xml");
//    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
//       // ui->label->setText("Config not exist!");
//    }
//    QXmlStreamReader xml(file);

//    xml.readNextStartElement();
//      //ui->label_2->setText(xml.name().toString());
//    xml.readNextStartElement();
//  //  ui->label_3->setText(xml.name().toString());

//    while (!xml.atEnd() && !xml.hasError()) {
//        QXmlStreamReader::TokenType token = xml.readNext();

//        if (token == QXmlStreamReader::StartElement) {

//            if (xml.name() == QString("zones")) {
//                //QXmlStreamAttributes attrib = xmlDoc.attributes();
//                //date = QDate::fromString(attrib.value("Date").toString(), "dd.MM.yyyy");
//                zones = xml.readElementText().toInt();
//                //ui->label_2->setText(xml.name().toString());
//                continue;
//            }
//            //            if (xmlDoc.name() == "Value") {
//            //                valRate = german.toDouble(xmlDoc.readElementText());
//            //                continue;
//            //            }
//        }
//        //        if (token == QXmlStreamReader::EndElement && xml.name() == "Record")
//        //            emit rate(date, valRate);

//    }

//}


