
#include "field.h"

Field::Field(QWidget *parent, int numberField, int zones) : QMainWindow(parent) {
    number = numberField;

    diagramU = new int[256];
    diagramI = new int[256];
    for(int j=0; j < 256; j++) {
        diagramI[j]=0;
        diagramU[j]=0;
    }
    first=last=0;

    if(zones > 4) left = 150;

    power = number > 1 ? 10 : 4;
    frame = new QFrame(parent);

    frame->setFrameShape(QFrame::Panel);
    frame->resize(width,height);
    frame->move(left + next*number, top);
    int fontSize = 12;
    QFont font( "Tahoma", fontSize);
    graph = new QGraphicsView(frame);
    graph->resize(gsize, gsize);
    graph->move(gleft, gtop);

    sc = new QGraphicsScene();
        graph->setScene(sc);

    pbU = new QProgressBar(frame);
        pbU->setGeometry(QRect(QPoint(pleft, putop), QSize(pwidth, pheight)));
        pbU->setTextVisible(false);
        pbU->setStyleSheet("QProgressBar::chunk{background-color: #9098f0; width: 1px; }");

    valU = new QLabel(" U =               kV", frame);
        valU->setFont(font);
        valU->move(uleft, utop);

    pbI = new QProgressBar(frame);
        pbI->setGeometry(QRect(QPoint(pleft, pitop), QSize(pwidth, pheight)));
        pbI->setTextVisible(false);
        pbI->setStyleSheet("QProgressBar::chunk {background-color: #20C0A0; width: 1px;}");

    valI = new QLabel(" I =               mA", frame);
        valI->setFont(font);
        valI->move(uleft, itop);

    mode = new QLabel("Авто          ", frame);
        mode->setFont(font);
        mode->move(mleft, mtop);

    start = new QPushButton("Пуск",frame);  // Create the button, make "frame" the parent
    start->setGeometry(QRect(QPoint(sleft,sttop), QSize(swidth, sheight))); // set size and location of the button
    start->setFont(font);

    stop = new QPushButton("Стоп",frame);
    stop->setGeometry(QRect(QPoint(sleft,sptop), QSize(swidth, sheight))); // set size and location of the button
    stop->setFont(font);

    shaking = new QLabel("Встряхивание",frame);
        shaking->setFont(font);
        shaking->move(shleft,shtop);

    vibr = new QLabel("~~~~",parent);
        font.setPointSize(20);
        vibr->setFont(font);
        vibr->move(left + vleft + next*number, top + vtop);

        connect(start, &QPushButton::released, this, &Field::on_start_clicked);
        connect(stop, &QPushButton::released, this, &Field::on_stop_clicked);
}

void Field::updateInfo(NetInfo &inf) {
    pbU->setValue(inf.u);
    valU->setText("U" + QString::number(number+1) +" = " + QString::number(inf.u) + "kV");

    pbI->setValue(inf.i);
    valI->setText("I" + QString::number(number+1) +" = " + QString::number(inf.i*power) + "mA");

    if(inf.flags & 1) mode->setText("Искра");
        else mode->setText("Авто");
    if(inf.flags & 0x80) mode->setText("Стоп");



    if(inf.shake){
        shaking->setText("Встряхивание");
        vibr->setText("~~~~");
    }
    else {
        shaking->setText(""); vibr->setText("");
    }

}

void Field::diagram(NetInfo & data) {

    diagramU[last] = data.u;
    diagramI[last] = data.i;

    last=(++last)%256;
    //if(!last) first =1;
    sc->clear();
    pen.setColor(0xe0e0e0);
    pen.setWidth(1);
    for(int j=1; j <10; j++)
        sc->addLine(j*18, -89, j*18, 89, pen);  // 186*182
    for(int j=1; j <10; j++)
        sc->addLine(1, -90+18*j, 179,-90+18*j, pen);

    pen.setColor(0x9098f0);  //f05858
    pen.setWidth(2);

    for(unsigned int j =1; j<dsize-2; j++ ) {
        pen.setColor(0x9098f0);  //f05858
        sc->addLine((dsize -j), 1.8*diagramU[(last-j)%256]-89, (dsize -j-1), 1.8*diagramU[(last-j-1)%256]-89,pen);

        pen.setColor(0x20C0A0);  //f05858
        sc->addLine((dsize -j), 88-0.9*diagramI[(last-j)%256], (dsize -j-1), 88-0.9*diagramI[(last-j-1)%256],pen);
    }

}

void Field::on_start_clicked()
{
    Channel::status |= 1 << number;
    mode->setText(QString::number(Channel::status) );
}

void Field::on_stop_clicked()
{
    Channel::status &= 0xf ^ 1 << number;
    mode->setText(QString::number(Channel::status) );
}

void Field::setPower(float power)
{
    this->power = power/100;
}

