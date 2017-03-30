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

    QScrollArea* area = new QScrollArea(this);

    markWidget = new MarkWidget(this);
    area->setWidget(markWidget);

    setCentralWidget(area);

    markWidget->setImage(&image);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
}
