#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "channel.h"
#include "field.h"
#include "config.h"

#include <QMainWindow>

#include <QProgressBar>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>

#include "netinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void update(NetInfo);

    void updatecmd(int);

    void on_pushButton_2_clicked();

protected :
    Ui::MainWindow *ui;
    int count=0;
    int zones = 4;
    Field **fields;
    Config *config;


    void paintEvent(QPaintEvent*) override;

signals:
    void sendcmd(unsigned int);

};

#endif // MAINWINDOW_H
