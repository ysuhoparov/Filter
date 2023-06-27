#include "field.h"

Field::Field(QWidget *parent, int numberField, int zones) : QMainWindow(parent) {
    number = numberField;

    diagramU = new int[256];
    diagramI = new int[256];
    for(int j=0; j < 256; j++) {
        diagramI[j] = diagramU[j] = 0;
    }
    first=last=0;

    if(zones > 4) left = 150;

    frame = new QFrame(parent);
    frame->setFrameShape(QFrame::Panel);
    frame->resize(width,height);
    frame->move(left + next*number, top);

    graph = new QGraphicsView(frame);
    graph->resize(gsize, gsize);
    graph->move(gleft, gtop);

    sc = new QGraphicsScene();
    graph->setScene(sc);

    sdigit(frame);

    pbU = new QProgressBar(frame);
        pbU->setGeometry(QRect(QPoint(pleft, putop), QSize(pwidth, pheight)));
        pbU->setTextVisible(false);
        pbU->setStyleSheet("QProgressBar::chunk{background-color: #9098f0; width: 1px; }");
    QFont font( "Tahoma", 8);
    font.setPointSize(12);
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

void Field::updateInfo() {
    pbU->setValue(data.u);
    valU->setText("U" + QString::number(number+1) +" = " + QString::number(data.u) + "kV");

    pbI->setValue(data.i);
    valI->setText("I" + QString::number(number+1) +" = " + QString::number(data.i*power) + "mA");

    if(data.flags & 1) mode->setText("Искра");
        else mode->setText("Авто");
    if(data.flags & 0x80) mode->setText("Стоп");

    if(data.shake){
        shaking->setText("Встряхивание");
        vibr->setText("~~~~");
    }
    else {
        shaking->setText("");
        vibr->setText("");
    }

    diagram();
}

// Отрисовка диаграмм тока и напряжения электрофильтра
void Field::diagram() {
    diagramU[last] = data.u < 99 ? data.u : 98;  // Новые значения
    diagramI[last] = data.i < 99 ? data.i : 98;  // -1 на толщину линии

    last=(++last)%256;   // Подготовка следующего индекса
    // Прорисовка сетки
    sc->clear();
    pen.setColor(0xe0e0e0);
    pen.setWidth(1);
    for(int j=0; j <8; j++)
        sc->addLine(j*dt+gd, -dh, j*dt+gd, dh, pen);  //
    for(int j=1; j <10; j++)
        sc->addLine(1, -dh-1+dm*j, 179,-dh-1+dm*j, pen);

    // Построение графиков, U-двойной толщины
    for(unsigned int j = gd*2; j<dsize-gd; j++ ) {
        pen.setWidth(1);
        pen.setColor(0x20C0A0);  // Цвет I
        sc->addLine((dsize -j), dh-dmi*diagramI[(last-j)%256], (dsize -j-1), dh-dmi*diagramI[(last-j-1)%256],pen);
        pen.setWidth(2);
        pen.setColor(0x9098f0);  // Цвет U
        sc->addLine((dsize -j), dmu*diagramU[(last-j)%256]-dh, (dsize -j-1), dmu*diagramU[(last-j-1)%256]-dh,pen);

    }
}

// Нажатие Пуск
void Field::on_start_clicked()
{
    Channel::status |= 1 << number;
    mode->setText(QString::number(Channel::status) );
}
// Нажатие Стоп
void Field::on_stop_clicked()
{
    Channel::status &= 0xf ^ 1 << number;
    mode->setText(QString::number(Channel::status) );
}

void Field::setPower(float power)
{
    this->power = power/100;
}

void Field::sdigit(QFrame* frame)
{
    QFont font( "Tahoma", 8);

    diaglbl = new QLabel("-60   50    40   30    20    10 c", frame);
    diaglbl->setFont(font);
    diaglbl->move(glbleft, glbltop);

    du20 = new QLabel("20", frame);
    du20->setFont(font);
    du20->move(duleft, d20top);
    du50 = new QLabel("50", frame);
    du50->setFont(font);
    du50->move(duleft, d50top);
    du80 = new QLabel("80kV", frame);
    du80->setFont(font);
    du80->move(duleft, d80top);

    di80 = new QLabel("80%", frame);
    di80->setFont(font);
    di80->move(dileft-10, d20top);
    di50 = new QLabel("50", frame);
    di50->setFont(font);
    di50->move(dileft, d50top);
    di20 = new QLabel("20", frame);
    di20->setFont(font);
    di20->move(dileft, d80top);
}
