#include "timebar.h"

#include <QtWidgets>

TimeBar::TimeBar()
{
}

QRectF TimeBar::boundingRect() const
{
    return QRect(0,0,m_filledX, m_y);
}
void TimeBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(widget);

    QColor fillColor = Qt::red;

    painter->fillRect(QRectF(0, 0, m_filledX, 10), fillColor);
    qDebug() << "drawing size to " << m_filledX;
}
void TimeBar::SetFilledPercentage(float percentage)
{
    m_filledX = m_x * percentage;
    //update();


}
void TimeBar::SetSize(int x, int y)
{
    m_x = x;
    m_y = y;
}
