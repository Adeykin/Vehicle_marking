#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QLabel>
#include <QVector>
#include <QPoint>

#include <markwidget.h>

#include <list>

namespace Ui {
class MainWindow;
}

struct MarkedImage
{
    QString fullPath;
    QString fileName;
    QVector<QVector<QPoint>> poligons;
    QImage* image = nullptr;

    ~MarkedImage()
    { delete image; }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void open();
    void save();
    void prevImage();
    void nextImage();

protected:
    void paintEvent(QPaintEvent* e);

private:
    Ui::MainWindow *ui;
    QImage image;
    QWidget* widget;
    QLabel* label;
    QPixmap *myPix;
    QPicture* picture;
    MarkWidget* markWidget;

    QFile file;

    QVector<MarkedImage> images;
    int currentImage = 0;

    void updateImage();
};

#endif // MAINWINDOW_H
