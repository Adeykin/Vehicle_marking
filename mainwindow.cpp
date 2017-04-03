#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>
#include <string>

#include <QLabel>
#include <QScrollArea>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    //image("/home/adeykin/projects/parking/115000004/901000011/20170327_121030.jpg")
{
    ui->setupUi(this);

    QScrollArea* area = new QScrollArea(this);

    markWidget = new MarkWidget(this);
    area->setWidget(markWidget);

    setCentralWidget(area);

    //markWidget->setImage(&image);

    //QObject::connect(ui->menuFile, SIGNAL(triggered()),this, SLOT(openFileList()));
    QMenu* menu = ui->menuBar->addMenu("File");
    QAction* actOpen = new QAction("Open", this);
    QAction* actSave = new QAction("Save", this);
    menu->addAction(actOpen);
    menu->addAction(actSave);
    connect(actOpen, SIGNAL(triggered(bool)), this, SLOT(open()));
    connect(actSave, SIGNAL(triggered(bool)), this, SLOT(save()));

    QAction* actPrev = new QAction("<<", this);
    QAction* actNext = new QAction(">>", this);
    ui->mainToolBar->addAction(actPrev);
    ui->mainToolBar->addAction(actNext);
    connect(actPrev, SIGNAL(triggered(bool)), this, SLOT(prevImage()));
    connect(actNext, SIGNAL(triggered(bool)), this, SLOT(nextImage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open images list"));
    qDebug() << "Opening file: " << fileName;

    //QFile file(fileName);
    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QFileInfo fileInfo(file);
    QString path = fileInfo.absoluteDir().path();

    qDebug() << "path: " << path;

    while (!file.atEnd()) {
        QString line = file.readLine();
        QString imageName = line;
        imageName = imageName.left(imageName.size()-1);
        //qDebug() << "Reading line: " << line;
        QString fullImageName = path + QDir::separator() + imageName;
        MarkedImage markedImage;
        markedImage.fullPath = fullImageName;
        markedImage.fileName = imageName;
        images.push_back(markedImage);
    }
    qDebug() << images.size() << " images was loaded";

    updateImage();
}

void MainWindow::save()
{
    file.resize(0);
    QTextStream out(&file);
    for(auto it = images.begin(); it != images.end(); it++)
    {
        out << it->fileName;
        for(auto poligonIt = it->poligons.begin(); poligonIt != it->poligons.end(); poligonIt++)
        {
            out << ' ' << (*poligonIt)[0].x()
                 << ' ' << (*poligonIt)[1].x()
                 << ' ' << (*poligonIt)[2].x()
                 << ' ' << (*poligonIt)[3].x();
        }
        out << '\n';
    }
}

void MainWindow::prevImage()
{
    qDebug() << "prev Image" << currentImage-1;

    if(currentImage<=0)
        return;

    //Loading markers
    images[currentImage].poligons = markWidget->getPoligons();
    markWidget->erasePoligons();

    delete images[currentImage].image;
    images[currentImage].image = nullptr;
    currentImage--;
    images[currentImage].image = new QImage(images[currentImage].fullPath);

    markWidget->setImage(images[currentImage].image);
    markWidget->setPoligons( images[currentImage].poligons );

    markWidget->update();
}

void MainWindow::nextImage()
{
    qDebug() << "next Image" << currentImage+1;

    if(currentImage>=images.size()-1)
        return;

    //Loading markers
    images[currentImage].poligons = markWidget->getPoligons();
    markWidget->erasePoligons();

    delete images[currentImage].image;
    images[currentImage].image = nullptr;
    currentImage++;
    images[currentImage].image = new QImage(images[currentImage].fullPath);

    markWidget->setImage(images[currentImage].image);

    //Set markers
    if(images[currentImage].poligons.size() == 0)
        markWidget->setPoligons( images[currentImage-1].poligons );
    else
        markWidget->setPoligons( images[currentImage].poligons );

    markWidget->update();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
}

void MainWindow::updateImage()
{
    MarkedImage& markedImage = images[currentImage];
    markedImage.image = new QImage(markedImage.fullPath);

    markWidget->setImage(markedImage.image);
    markWidget->update();
}
