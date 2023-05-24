#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "channel.h"
#include "field.h"

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
    void on_pushButton_clicked();
        void updatecmd(int);

    void on_pushButton_2_clicked();

protected :
    Ui::MainWindow *ui;
    int count=0;
    Field **fields;

    void paintEvent(QPaintEvent*) override;

signals:
    void sendcmd(unsigned int);

};

#endif // MAINWINDOW_H
