#include "game.h"
#include "gameboard.h"
#include "tile.h"
#include "star.h"

#include <QPixmap>
#include <QGraphicsScene>

#include <QtDebug>

#include "gamewindow.h"

#define SCREENSIZEX 1024
#define SCREENSIZEY 600

#define TILESIZE 64
#define TILEOFFSET 8
#define BOARDOFFSET SCREENSIZEX / 5

GameBoard::GameBoard()
{
    pixmap = new QPixmap;
    pixmap->load("../Resources/Icon_Back.png");

    m_width = 0;
    m_height = 0;

    m_tiles = 0;
	m_stars = 0;
    window = 0;

    scene = new QGraphicsScene(0);
	scene->setSceneRect(0,0, SCREENSIZEX,SCREENSIZEY);


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

    RandomizeBoard();

	m_stars = new Star[3];
	for(int i = 0; i < 3; i++)
	{
		m_stars[i].setPos(20, 30 + 140*i);
		scene->addItem(&m_stars[i]);
	}

    for(int y = 0; y < m_height; y++)
        for(int x = 0; x < m_width; x++)
        {
            int i = y * m_width + x;
			m_tiles[i].setPos(x*TILESIZE+TILEOFFSET*x + BOARDOFFSET, y*TILESIZE+TILEOFFSET*y + TILESIZE/2);

			scene->addItem(&m_tiles[i]);
        }

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
    if(m_tiles)
    {
        for(int i = 0; i < m_width*m_height; i++)
        {
            m_tiles[i].setFacingToTop();
        }
    }
}

 void GameBoard::RandomizeBoard()
 {
     if(m_tiles)
         for(int i = 0; i < m_width*m_height; i++)
         {
             int rand = qrand() % (Game::I().m_animals.size());
             m_tiles[i].SetAnimal(Game::I().m_animals[rand]);
         }
 }

 QList<Tile*>& GameBoard::GetOpenTiles()
 {
     QList<Tile*> list;

     if(m_tiles)
         for(int i = 0; i < m_width*m_height; i++)
         {
             if(m_tiles[i].m_facing == Tile::FS_BOTTOM)
                 list.push_back(&m_tiles[i]);
         }
 }

 Tile* GameBoard::GetRandomTile()
 {
	 return &m_tiles[qrand() % (m_width*m_height)];
 }


 void GameBoard::SetBoardTop()
 {
	 ResetBoard();
 }

 void GameBoard::SetBoardBottom()
 {
	 if(m_tiles)
	 {
		 for(int i = 0; i < m_width*m_height; i++)
		 {
			 m_tiles[i].setFacingToBottom();
		 }
	 }
 }
