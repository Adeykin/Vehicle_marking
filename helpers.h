#ifndef HELPERS_H
#define HELPERS_H

#include <QVector>
#include <QPoint>

bool isInsidePoligon(const QVector<QPoint>& poligon, QPoint point);
double dot(QPoint a, QPoint b);
QPoint normal(QPoint vec);
QPoint prevPoint(const QVector<QPoint>& poligon, int index);

#endif // HELPERS_H

