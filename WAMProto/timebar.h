#ifndef TIMEBAR_H
#define TIMEBAR_H

#include <QGraphicsItem>

class TimeBar : public QGraphicsItem
{
public:
    TimeBar();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

    void SetFilledPercentage(float percentage);

    void SetSize(int x, int y);


    int m_x;
    int m_y;
    int m_filledX;

};

#endif // TIMEBAR_H
