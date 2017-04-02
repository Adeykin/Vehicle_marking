#ifndef MARKWIDGET_H
#define MARKWIDGET_H

#include <QWidget>

#include <list>

class MarkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MarkWidget(QWidget *parent = 0);

    void setImage(QImage* image);

    QVector<QVector<QPoint>> getPoligons();
    void setPoligons(QVector<QVector<QPoint>>);
    void erasePoligons();

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

protected:
    void paintEvent(QPaintEvent* e);
private:
    QImage* image = NULL;
    QVector<QPoint> points;
    QVector<QVector<QPoint>> poligons;
signals:

public slots:
};

#endif // MARKWIDGET_H
