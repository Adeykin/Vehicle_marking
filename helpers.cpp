#include <helpers.h>
#include <assert.h>

bool isInsidePoligon(const QVector<QPoint>& poligon, QPoint point)
{
    assert(poligon.size() >= 3);

    bool oneSide = true;
    bool firstSign;
    for(int i = 0; i < poligon.size(); i++)
    {
        QPoint curr = poligon[i];
        QPoint prev = prevPoint(poligon,i);

        QPoint norm = normal(curr-prev);
        bool under = dot(norm, point-prev) > 0;
        if(i == 0)
            firstSign = under;
        else
            oneSide &= firstSign == under;
    }
    return oneSide;
}

double dot(QPoint a, QPoint b)
{
    return a.x()*b.x() + a.y()*b.y();
}

QPoint normal(QPoint vec)
{
    return QPoint(-vec.y(), vec.x());
}

QPoint prevPoint(const QVector<QPoint>& poligon, int index)
{
    return index == 0 ? poligon.back() : poligon[index-1];
}


