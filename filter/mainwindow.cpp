#include "mainwindow.h"
#include "dataconversion.h"
#include "report.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    // Чтение конфигурационного файла
    config = new Config();
    zones = config->getZones();

    ui->setupUi(this);

    QWidget *widget = new QWidget;
    // для меню
    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topFiller);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);

    setWindowTitle("Система управления электрофильтром " + config->name);
    resize(1280, 720);

    createActions();
    createMenus();

    if(config->success)
        statusBar()->showMessage("Config file wrong - Demo mode");

// Подключение к СуБД
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("db.sqlite3");
    db.setUserName("");
    db.setPassword("");

    if(db.open()) statusBar()->showMessage("Db is open");

    if(!config->success)
        statusBar()->showMessage("Config file wrong - Demo mode");


// Инициализация отображения полей фильтра
    fields = new Field*[zones];
    for(int i = 0; i < zones; i++) {
        fields[i] = new Field(this , i, zones);
        fields[i]->setPower(config->getPower(i));
    }

// Создание потока для канала связи с контроллерами полей электрофильтра
    QThread *thread= new QThread;
    Channel *channel = new Channel();

    channel->moveToThread(thread);
    connect(channel, SIGNAL(send(NetInfo)), this, SLOT(update(NetInfo)));
    connect(thread, SIGNAL(started()), channel, SLOT(network()));
    thread->start();
}


MainWindow::~MainWindow()
{
    for(int i = 0; i < zones; i++)
        delete fields[i];
    delete  fields;

    delete config;
    delete ui;
}

// Дорисовка бункеров, входной и выходной зон фильтра
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

void MainWindow::parameters()
{
    Report::parameters();
}

void MainWindow::service()
{   
    Report::service();
}

void MainWindow::save()
{
    ;  // future
}

void MainWindow::print()
{
    ; // future
}

void MainWindow::aboutFilter()
{
    const char * aboutFilter{ R"(
    Электрофильтр — это устройство для очистки газов от аэрозольных,
твердых или жидких частиц происходит под действием электрического поля.
В результате действия электрических сил заряженные частицы выводятся из
очищаемого газового потока и осаждаются на электродах. Зарядка частиц
происходит в поле коронного разряда.

    Электрофильтр представляет собой корпус прямолинейной или
цилиндрической формы, внутри которого смонтированы осадительные и
коронирующие электроды. Коронирующие электроды подключены к
высоковольтному источнику питания напряжением 50—60 кВ.

    Электрофильтры, в которых улавливаемые частицы
удаляются с электродов встряхиванием, называются сухими, а те,
в которых осаженные частицы смываются с электродов жидкостью или
улавливаются жидкие частицы (туман, брызги), — мокрыми.

    По числу электрических полей, через которые очищаемый газ проходит
последовательно электрофильтры разделяют на однопольные и многопольные.
Иногда электрофильтры разбивают на параллельные по ходу газа  секции.

    Очищаемый в электрофильтре газ проходит активную зону в вертикальном
или горизонтальном направлениях. По типу осадительных электродов
электрофильтры делят на пластинчатые и трубчатые. )" };

    QMessageBox::about(this, tr("About Filter"), tr(aboutFilter));
}

void MainWindow::about(){
    const char * about{ R"(
    Система управления электрофильтром работает совместно с контроллерами
полей фильтра, которые выполняют непосредственное управление источниками
питания и механизмами регенерации фильтра.

    Система ведет сбор и хранение в базе данных информации о режимах
питания фильтра, выходе из строя и замене элементов оборудования
электрофильтра.

    Система позволяет проводить управление источниками питания фильтра
(пуск - стоп) и установку параметров алгоритма регулирования напряжения
источников питания электрофильтра.  )" };

    QMessageBox::about(this, tr("About"), tr(about));
}


void MainWindow::createActions()
{
    paramAct = new QAction(tr("&Параметры питания"), this);
    paramAct->setShortcuts(QKeySequence::Underline);   // CtrlU
    paramAct->setStatusTip(tr("Параметры питания полей фильтра"));
    connect(paramAct, &QAction::triggered, this, &MainWindow::parameters);

    serviceAct = new QAction(tr("&Обслуживание"), this);
    serviceAct->setShortcuts(QKeySequence::Open);  // CtrlO
    serviceAct->setStatusTip(tr("Ведомость технического обслуживания"));
    connect(serviceAct, &QAction::triggered, this, &MainWindow::service);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print the document"));
    connect(printAct, &QAction::triggered, this, &MainWindow::print);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Cut);  // CtrlX
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::close);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    aboutFilterAct = new QAction(tr("&AboutFilter"), this);
    aboutFilterAct->setStatusTip(tr("Show the application's AboutFilter box"));
    connect(aboutFilterAct, &QAction::triggered, this, &MainWindow::aboutFilter);
}

void MainWindow::createMenus()
{
    reportMenu = menuBar()->addMenu(tr("&Отчеты"));
    reportMenu->addAction(paramAct);
    reportMenu->addAction(serviceAct);
    reportMenu->addAction(saveAct);
    reportMenu->addAction(printAct);
    reportMenu->addSeparator();
    reportMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutFilterAct);
}

void MainWindow::update(NetInfo data)
{
    static int lastsec=QDateTime::currentDateTime().time().second();
    // Отображение полученной по каналу связи информации
    if(data.field <= zones and data.field > 0) {
        fields[data.field-1]->data = data;
        fields[data.field-1]->updateInfo();
        // Store data
        QDateTime cdt = QDateTime::currentDateTime();
        if(lastsec != cdt.time().second()) {
            lastsec = cdt.time().second();
            QSqlQuery query;
            query.prepare("INSERT INTO history ( timerec, field1, field2, field3, field4 ) "
                     "VALUES (:timerec, :f1, :f2, :f3, :f4)");
            query.bindValue(":timerec", cdt);
            DataConversion dc;
            query.bindValue(":f1", dc.incode(fields[0]->data));
            query.bindValue(":f2", dc.incode(fields[1]->data));
            if(zones > 2)
                query.bindValue(":f3", dc.incode(fields[2]->data));
            if(zones > 3)
                query.bindValue(":f4", dc.incode(fields[3]->data));

            query.exec();
            if(query.lastError().text()!="")
                statusBar()->showMessage(query.lastError().text());
        }
    }
}

