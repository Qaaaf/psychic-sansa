#include "gameboard.h"
#include "tile.h"

#include <QPixmap>
#include <QGraphicsScene>

#include <QtDebug>

#include "gamewindow.h"

GameBoard::GameBoard()
{
    pixmap = new QPixmap;
    pixmap->load("../Resources/Icon_Back.png");

    m_width = 0;
    m_height = 0;

    m_tiles = 0;

    window = 0;

    scene = new QGraphicsScene(0);
}

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
    if(m_width < 1 || m_height < 1)
        return;

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
