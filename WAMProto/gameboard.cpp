#include "gameboard.h"
#include "tile.h"

#include <QPixmap>
#include <QGraphicsScene>

#include <QtDebug>

#include "gamewindow.h"

//QPixmap* p1;
//QPixmap* p2;
//QPixmap* p3;
//QPixmap* p4;
//QPixmap* p0;
//QPixmap* pDefault;

GameBoard::GameBoard()
{
//    p0 = new QPixmap;
//    p1 = new QPixmap;
//    p2 = new QPixmap;
//    p3 = new QPixmap;
//    p4 = new QPixmap;
//    pDefault = new QPixmap;

//    p0->load("../Resources/Icon_0.png");
//    p1->load("../Resources/Icon_1.png");
//    p2->load("../Resources/Icon_2.png");
//    p3->load("../Resources/Icon_3.png");
//    p4->load("../Resources/Icon_4.png");
//    pDefault->load("../Resources/Icon_Back.png");

    pixmap = new QPixmap;
    pixmap->load("../Resources/Icon_Back.png");

    m_width = 0;
    m_height = 0;

    m_tiles = 0;

    window = 0;

    scene = new QGraphicsScene(0);
}

//QPixmap& getmap()
//{
//    int i = rand()%5;
//    switch (i)
//    {
//    case 0:
//        return *p0;
//        break;
//    case 1:
//        return *p1;
//        break;
//    case 2:
//        return *p2;
//        break;
//    case 3:
//        return *p3;
//        break;
//    case 4:
//        return *p4;
//        break;
//    default:
//        return *pDefault;
//    }
//}

GameBoard::~GameBoard()
{
}

void GameBoard::OnTileClicked(Tile* tile)
{

}

void GameBoard::SetBoardXY(int x, int y)
{
    m_width = x;
    m_height = y;

    CreateBoard();
}

#define TILESIZE 64
#define TILEOFFSET 8

void GameBoard::CreateBoard()
{
    if(m_tiles)
    {
        scene->clear();
        //delete[] m_tiles;
        m_tiles=0;
    }

    m_tiles = new Tile[m_width*m_height];

    for(int y = 0; y < m_height; y++)
        for(int x = 0; x < m_width; x++)
        {
            int i = y * m_width + x;
            m_tiles[i].setPos(x*TILESIZE+TILEOFFSET*x,y*TILESIZE+TILEOFFSET*y);
            //m_tiles[i].setPixmap(getmap());

            scene->addItem(&m_tiles[i]);


        }
    scene->setSceneRect(0,0, 1024,768);
    scene->update();
    if(window)
        window->update();
}

void GameBoard::Update(float dt)
{
   // qDebug() << "tick.";

    for(int i = 0; i < m_width * m_height; i++)
    {
        m_tiles[i].Update(dt);
    }
}

void GameBoard::ResetBoard()
{
    CreateBoard();
}
