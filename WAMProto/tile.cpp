#include "tile.h"

#include <QPainter>
#include <QPainterPath>

#include <QtWidgets>
#include "gameboard.h"

#define TILESIZE 64
#define TILEOFFSET 8

#include <QPixmap>
#include <QGraphicsScene>

#include <QtDebug>

#include "gamewindow.h"

QPixmap* p1;
QPixmap* p2;
QPixmap* p3;
QPixmap* p4;
QPixmap* p0;
QPixmap* pDefault;

void MapPixmaps()
{
    p0 = new QPixmap;
    p1 = new QPixmap;
    p2 = new QPixmap;
    p3 = new QPixmap;
    p4 = new QPixmap;
    pDefault = new QPixmap;

    if(!p0->load("../Resources/Icon_0.png"))
        return;

    p1->load("../Resources/Icon_1.png");
    p2->load("../Resources/Icon_2.png");
    p3->load("../Resources/Icon_3.png");
    p4->load("../Resources/Icon_4.png");
    pDefault->load("../Resources/Icon_Back.png");

}

QPixmap* getmap()
{
    int i = rand()%5;
    switch (i)
    {
    case 0:
        return p0;
        break;
    case 1:
        return p1;
        break;
    case 2:
        return p2;
        break;
    case 3:
        return p3;
        break;
    case 4:
        return p4;
        break;
    default:
        return pDefault;
    }
}


bool once = true;
Tile::Tile()
{
    if(once)
        MapPixmaps();

    once = false;

    m_lastpixmap = pDefault;
    m_pixmap = getmap();
    SwitchPixmap();
    //x = 0;
    //y = 0;
    m_rotation = 0.0;
    m_direction = 1;

    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);

    setTransformOriginPoint(32,32);

    m_turnover = false;
}

Tile::~Tile()
{
}

void Tile::SwitchPixmap()
{
    QPixmap* p = m_pixmap;
    m_pixmap = m_lastpixmap;
    m_lastpixmap = p;
    setPixmap(*m_pixmap);
}

//void Tile::setPos(int x, int y)
//{
//    this->x = x*TILESIZE+TILEOFFSET;
//    this->y = y*TILESIZE+TILEOFFSET;

//    this->setX(x);
//    this->setY(y);
//}


void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
     //Q_UNUSED(widget);
    //if (item->state & QStyle::State_Selected)
    //    return;

    QGraphicsPixmapItem::paint(painter, item, widget);
    //painter->drawPixmap(x,y,this->pixmap());
}

QRectF Tile::boundingRect() const
{
    return QRectF(0, 0, 64, 64);
}

//QPainterPath Tile::shape() const
//{
//    QGraphicsItem::shape()
//    QPainterPath path;
//    //path.addRect(14, 14, 82, 42);
//    return path;
//}


void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);

    qDebug() << "clickevent";

    toFlippingState();

    update();
}

void Tile::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    if (event->modifiers() & Qt::ShiftModifier) {
//        stuff << event->pos();
//        update();
//        return;
//    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Tile::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}


void Tile::Update(float dt)
{
    QTransform m;

    switch(m_state)
    {
    case TS_FLIPPED:
    {
        updateFlippedState(dt);
        break;
    }
    case TS_FLIPPING:
    {
        updateFlippingState(dt);

        break;
    }
    default:
        break;
    }

    m.rotate(m_rotation, Qt::XAxis);
    m.translate(-32,-32);
    this->setTransform(m);
}

void Tile::toFlippedState()
{
    m_state = TS_FLIPPED;
}

#include "QAudio"
#include "QMediaPlayer"

void Tile::toFlippingState()
{
    if(m_state != TS_FLIPPING)
    {
       m_state = TS_FLIPPING;

       m_turnover = true;

       QMediaPlayer* player = new QMediaPlayer();
       player->setMedia(QUrl::fromLocalFile("../Resources/mallard_duck-Mike_Koenig-667013646.wav"));
       player->setVolume(50);
       player->play();
    }
    else
    {
    }

}

void Tile::updateFlippedState(float dt)
{
}

void Tile::updateFlippingState(float dt)
{
    if(m_rotation > 90.0 || m_rotation < 0.0)
    {
        if(m_turnover == true)
        {
            SwitchPixmap();
            m_turnover = false;
        }
        else
            toFlippedState();
        if(m_rotation > 90)
            m_rotation = 90.0;
        else
            m_rotation = 0.0;

        m_direction = -m_direction;


    }
    else
    {
        m_rotation += 90*dt*15*m_direction;
    }

    //QTransform m;// =;// this->transform();
    //m.rotate(rotation, Qt::XAxis);
    //m.rotate(rotation, Qt::YAxis);
    //m.translate(-32,-0);
    //this->setTransform(m);
}

