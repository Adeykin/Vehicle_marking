#include "markwidget.h"

#include <QDebug>
#include <QtGui>

#include <helpers.h>
#include <algorithm>

MarkWidget::MarkWidget(QWidget *parent) : QWidget(parent)
{
    //resize(500,500);
}

void MarkWidget::setImage(QImage *image)
{
    this->image = image;
    resize(image->size());
}

void MarkWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        qDebug() << "add point " << event->pos().x() << ' ' << event->pos().y();
        points.push_back( event->pos() );
        if(points.size() == 4)
        {
            qDebug() << "finish rect";
            poligons.push_back(points);
            points.clear();
        }
    }
    if(event->button() == Qt::RightButton)
    {
        qDebug() << "remove detection";
        poligons.erase(std::remove_if(poligons.begin(), poligons.end(),
            [event](const QVector<QPoint>& pol)
            {
                bool check = isInsidePoligon(pol, event->pos());
                qDebug() << "Check if need to remove " << check;
                return check;
            }
        ),
        poligons.end());

    }
    update();
}

void MarkWidget::mouseMoveEvent(QMouseEvent *event)
{
}

void MarkWidget::paintEvent(QPaintEvent *e)
{
    qDebug() << "painting MarkWidget";

    //QImage image("/home/adeykin/projects/parking/115000004/901000011/20170327_121030.jpg");

    if(image)
    {
        //Draw image
        QPixmap img = QPixmap::fromImage(*image);
        QPainter p(this);
        p.drawPixmap(0,0,img);

        //Draw all poligones
        p.setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap));
        for(auto it = poligons.begin(); it != poligons.end(); it++)
        {
            p.drawPolygon(*it);
        }

        //Draw current poligin
        p.setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap));
        p.drawPolyline(points);
    }
}

