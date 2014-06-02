#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>

//class QPixmap;
//class QPainter;
//class QStyleOptionGraphicsItem
//class QWidget


class Tile : public QGraphicsPixmapItem
{
public:
    Tile();
    ~Tile();

    void SwitchPixmap();

    //void setPosition(int x, int y);

    QRectF boundingRect() const;
    //QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


    void toFlippedState();
    void toFlippingState();

    void updateFlippedState(float dt);
    void updateFlippingState(float dt);

    enum TileState
    {
        TS_FLIPPED,
        TS_FLIPPING
    } m_state;



    void Update(float dt);

    bool m_turnover;

    double m_rotation;
    int m_direction;

    QPixmap* m_pixmap;
    QPixmap* m_lastpixmap;
};

#endif // TILE_H
