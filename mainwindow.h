#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QLabel>

#include <markwidget.h>

#include <list>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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

    std::list<QPoint> points;
};

#endif // MAINWINDOW_H
