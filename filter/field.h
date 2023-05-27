
#ifndef FIELD_H
#define FIELD_H

#include "channel.h"
#include <QMainWindow>

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QGraphicsView>
#include <QGraphicsScene>


class Field : public QMainWindow
{
    Q_OBJECT
public:
    explicit Field(QWidget *parent, int numberField=0, int zones =4);

    void updateInfo(NetInfo&);
    void diagram(NetInfo&);
    void sendCommand();
    void setPower(float);

    QFrame* frame;

    //signals:
public slots:
    void on_start_clicked();

    void on_stop_clicked();

private:

    QPen pen;

    int number;
    float power;


    QGraphicsView *graph;
    QGraphicsScene *sc;

    QProgressBar *pbU,*pbI;
    QLabel *valI, *valU, *mode, *shaking, *vibr;

    QPushButton *start, *stop;

    int *diagramU, *diagramI;
    unsigned int first, last;
    int count =10;

//sizes
    int width = 192;
    int height = 440;
    int left = 250;
    int next = width + 3;
    int top = 60;
    int gsize = width - 10;
    int gleft = 5;
    int gtop = 4;

    int pleft = 32;
    int pwidth = 128;
    int pheight = 8;
    int putop = 196;
    int pitop = 236;
    int uleft = 60;
    int utop = 208;
    int itop = 246;

    int mleft = 70;
    int mtop = 276;

    int sleft = 58;
    int sttop = 300;
    int swidth = 80;
    int sheight = 28;
    int sptop = 329;

    int shleft = 40;
    int shtop = 400;
    int vleft = 50;
    int vtop = 460;

    unsigned int dsize = 180;  // points of diagram


};

#endif // FIELD_H
