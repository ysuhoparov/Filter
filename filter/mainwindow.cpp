#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    config = new Config();

    zones = config->getZones();

    fields = new Field*[zones];

    for(int i = 0; i < zones; i++) {
        fields[i] = new Field(this ,i);
        fields[i]->setPower(config->getPower(i));

    }

    QThread *thread= new QThread;
    Channel *channel = new Channel();

    channel->moveToThread(thread);
    connect(channel, SIGNAL(send(NetInfo)), this, SLOT(update(NetInfo)));
    connect(thread, SIGNAL(started()), channel, SLOT(network()));
    thread->start();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete config;
}

void MainWindow::update(NetInfo data)
{
    if(data.field <= zones) {
        fields[data.field-1]->updateInfo(data);
        fields[data.field-1]->diagram(data);
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label_2->setText(QString::number(count++));
    Channel::status =15;
}


//void MainWindow::on_pushButton_clicked()
//{
//    ui->label_2->setText(QString::number(count++));
//    Channel::status =0;

//    QThread *threadcmd= new QThread;
//    CmdChannel *cmdchannel = new CmdChannel(0x200);

//    cmdchannel->moveToThread(threadcmd);
//    connect(cmdchannel, SIGNAL(sendcmd(int)), this, SLOT(updatecmd(int)));
//    connect(threadcmd, SIGNAL(started()), cmdchannel, SLOT(command()));
//    threadcmd->start();;
//}

void MainWindow::updatecmd(int qwer)
{
ui->label->setText(QString::number(qwer));
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    for(int i =0; i < zones; i++) {
        auto f = fields[i]->frame;
        painter.drawLine(f->x(), f->y()+f->height(), f->x()+80, f->y()+f->height() + 140);
        painter.drawLine(f->x()+f->width(), f->y()+f->height(),
                         f->x()+f->width()-80, f->y()+f->height() + 140);
        painter.drawLine(f->x()+80, f->y()+f->height() + 140,
                         f->x()+f->width()-80, f->y()+f->height() + 140);
        if(!i) {
            painter.drawLine(f->x(), f->y(), f->x() - 100, f->y() +180);
            painter.drawLine(f->x(), f->y()+f->height(), f->x()-100, f->y()+f->height()-180);
            painter.drawLine(f->x() - 100, f->y() +180, f->x() - 100, f->y()+f->height()-180);
        }
        if(i == zones-1) {
            painter.drawLine(f->x()+f->width(), f->y(), f->x()+f->width()+100, f->y() +180);
            painter.drawLine(f->x()+f->width(), f->y()+f->height(), f->x()+f->width()+100, f->y()+f->height()-180);
            painter.drawLine(f->x()+f->width()+100, f->y()+f->height()-180, f->x()+f->width()+100, f->y() +180);
        }
    }
    painter.end();

}



