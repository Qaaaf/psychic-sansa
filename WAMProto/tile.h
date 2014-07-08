#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>

//class QPixmap;
//class QPainter;
//class QStyleOptionGraphicsItem
//class QWidget

class QMediaPlayer;
class Animal;
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

    void setFacingToTop();
    void setFacingToBottom();

    void ResetTilesState();

    void toFlippedState();
    void toFlippingState();

    void updateFlippedState(float dt);
    void updateFlippingState(float dt);

    void SetAnimal(Animal* animal);
	void SetTargetTilePixmap(Animal* animal);

    void Flip();

    enum TileState
    {
        TS_FLIPPED,
        TS_FLIPPING
    } m_state;

    enum FaceState
    {
        FS_TOP,
        FS_BOTTOM
    } m_facing;

    void Update(float dt);

    bool m_turnover;
	bool m_targetTile;

    double m_rotation;
    int m_direction;

    Animal* m_animal;

    QPixmap* m_pixmap;
    QPixmap* m_lastpixmap;
    QMediaPlayer* player;
};

#endif // TILE_H
