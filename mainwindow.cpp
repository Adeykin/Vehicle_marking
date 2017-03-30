#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <QPaint>
#include <QLabel>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    image("/home/adeykin/projects/parking/115000004/901000011/20170327_121030.jpg")
{
    ui->setupUi(this);

    myPix = new QPixmap();

    picture = new QPicture();

    //QWidget* widget = new Widget();
    //label = new QLabel("Long long label!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Long long label!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Long long label!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Long long label!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    label = new QLabel(this);
    //label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    //label->setScaledContents(true);
    QScrollArea* area = new QScrollArea(this);
    widget = new QWidget(area);
    widget->resize(1000,1000);


    area->setWidget(label);

    setCentralWidget(area);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "Mouse release";
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPixmap img = QPixmap::fromImage(image);
    QPainter painter;
    painter.begin(&img);
    painter.drawText(100,100,100,50,NULL,"Hello", NULL);
    //painter.drawPixmap(0,0,QPixmap::fromImage(image));
    painter.end();

    //QPixmap img = QPixmap::fromImage(image);
    //label->setPixmap(0,0,*myPix);
    label->setPixmap(img);
    label->resize(img.size());


    //setPixmap(QPixmap::fromImage(image));
}
