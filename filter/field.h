
#ifndef FIELD_H
#define FIELD_H

#include "channel.h"
#include "netinfo.h"

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
    // объявление дружественного класса
    friend class DataConversion;
public:
    explicit Field(QWidget *parent, int numberField=0, int zones =4);

    void updateInfo();
    void diagram();
    void sendCommand();
    void setPower(float);
    inline void sdigit(QFrame* frame);

    QFrame* frame;
    NetInfo data;

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
    QLabel *diaglbl, *valI, *valU, *mode, *shaking, *vibr;
    QLabel *du20, *du50, *du80, *di20, *di50, *di80; // Оцифровка графиков

    QPushButton *start, *stop;

    int *diagramU, *diagramI;
    unsigned int first, last;

//sizes
    int width = 192;        // Ширина панели поля фильтра
    int height = 440;       // Высота -//-
    int left = 250;         // Левый край панели поля фильтра
    int next = width + 3;   // Шаг для следующей панели
    int top = 60;           // верх панели поля фильтра
    int gsize = width - 10; // размеры области диаграмм
    int gleft = 5;          // отступы области диаграмм
    int gtop = 4;
    int glbleft = 24;       // Левый край подписи оси времени диаграмм
    int glbltop = 186;         // положение от верха подписи оси времени диаграмм
    int gd = 2;             // отступы графика по горизонтали

    int duleft = 4;             // отступы графика по горизонтали
    int dileft = 172;             // отступы графика по горизонтали
    int d20top = 32;
    int d50top = 86;
    int d80top = 140;

    int pleft = 32;         // Левый край линейного индикатора
    int pwidth = 128;       // Длина линейного индикатора
    int pheight = 8;        // Ширина линейного индикатора
    int putop = 220;        // Верх линейного индикатора U
    int pitop = 260;        // Верх линейного индикатора I
    int uleft = 60;         // координата X вывода значения U, I
    int utop = 232;         // координата Y вывода значения U
    int itop = 272;         // координата Y вывода значения I

    int mleft = 70;         // координаты вывода режима
    int mtop = 300;

    int sleft = 58;         // координаты и размеры кнопок Пуск, Стоп
    int sttop = 340;
    int swidth = 80;
    int sheight = 28;
    int sptop = 369;

    int shleft = 40;        // координаты вывода состояния регенерации
    int shtop = 410;
    int vleft = 50;         // координаты вывода состояния вибраторов бункеров
    int vtop = 460;

    unsigned int dsize = gsize-2; // 180;  // points of diagram -1 border
    int dh = 89;   // смещение графика по высоте
    int dm = 18;   // масштаб Y - 1 клетка (10 ед.) = 18 точек экрана  (вся диаграмма - 180 точек)
    int dt = 25;   // масштаб X - 1 клетка (10 c) = 25 точек экрана  (вся диаграмма - 175 точек)
    float dmu = 1.8;   // к-т масштабиолвания напряжения  0-80кV
    float dmi = 1.8;   // к-т масштабиолвания тока  диапазон 0-100%
};

#endif // FIELD_H
