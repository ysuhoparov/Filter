#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "netinfo.h"
#include "channel.h"
#include "field.h"
#include "config.h"


#include <QMainWindow>

#include <QProgressBar>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableView>

#include <QDateTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QAction;
class QLabel;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;
    int count=0;
    int zones = 4;
    Field **fields;
    Config *config;

    void paintEvent(QPaintEvent*) override;

private slots:
    void parameters();
    void service();
    void save();
    void print();

    void about();
    void aboutFilter();

    void update(NetInfo);

private:
    void createActions();
    void createMenus();

    QMenu *reportMenu;
    QMenu *helpMenu;

    QAction *paramAct;
    QAction *serviceAct;
    QAction *saveAct;
    QAction *printAct;
    QAction *exitAct;


    QAction *aboutAct;
    QAction *aboutFilterAct;

signals:
    void sendcmd(unsigned int);
};
#endif // MAINWINDOW_H
