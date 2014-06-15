#include "game.h"
#include "gameboard.h"
#include "tile.h"
#include "star.h"

#include <QPixmap>
#include <QGraphicsScene>

#include <QtDebug>

#include "gamewindow.h"

#define NUMSTARS 3

#define SCREENSIZEX 1024
#define SCREENSIZEY 600

#define TILESIZE 64
#define TILEOFFSET 8
#define BOARDOFFSET (SCREENSIZEX / 5)



GameBoard::GameBoard()
{
    pixmap = new QPixmap;
    pixmap->load("../Resources/Icon_Back.png");

    m_width = 0;
    m_height = 0;

    m_tiles = 0;
	m_targetTile = 0;
	m_stars = 0;
    window = 0;

    scene = new QGraphicsScene(0);
	scene->setSceneRect(0,0, SCREENSIZEX,SCREENSIZEY);


}

GameBoard::~GameBoard()
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

	if(m_targetTile)
		delete m_targetTile;

	m_targetTile = new Tile();
	m_targetTile->setAcceptedMouseButtons(false);
	m_targetTile->setPos(80, 520);
	scene->addItem(m_targetTile);

    m_tiles = new Tile[m_width*m_height];

    RandomizeBoard();

	m_stars = new Star[NUMSTARS];
	for(int i = 0; i < NUMSTARS; i++)
	{
		m_stars[i].setPos(20, 30 + 140*i);
		scene->addItem(&m_stars[i]);
	}

	ResetStars();

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

	m_targetTile->Update(dt);
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

	if(m_targetTile)
	{
		int rand = qrand() % (Game::I().m_animals.size());
		m_targetTile->SetAnimal(Game::I().m_animals[rand]);
	}
 }

 QList<Tile*> GameBoard::GetOpenTiles()
 {
     QList<Tile*> list;

     if(m_tiles)
         for(int i = 0; i < m_width*m_height; i++)
         {
             if(m_tiles[i].m_facing == Tile::FS_BOTTOM)
                 list.push_back(&m_tiles[i]);
         }

	 return list;
 }

 QList<Tile*> GameBoard::GetTilesOfType(Animal* animal)
 {
	 QList<Tile*> list;

	 if(m_tiles)
		 for(int i = 0; i < m_width*m_height; i++)
		 {
			 if(m_tiles[i].m_animal == animal)
				 list.push_back(&m_tiles[i]);
		 }

	 return list;
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

 void GameBoard::FlipBoard()
 {
	 if(m_tiles)
	 {
		 for(int i = 0; i < m_width*m_height; i++)
		 {
			 m_tiles[i].Flip();
		 }
	 }
 }

 void GameBoard::SeedBoard(Animal *seed, int numSeeds)
 {
	 QList<Animal*> tempanimals = Game::I().m_animals;

	 for(int i = 0; i < tempanimals.size();i++)
	 {
		 if(seed == tempanimals[i])
		 {
			 tempanimals.removeAt(i);
			 continue;
		 }
	 }

	 int size = tempanimals.size();
	 if(m_tiles)
	 {
		 for(int i = 0; i < m_width*m_height; i++)
		 {
			 int rand = qrand() % size;
			 m_tiles[i].SetAnimal(tempanimals[rand]);
		 }

		int r = qrand() % m_width*m_height;

		for(int i = 0; i< numSeeds; i++)
		{
			while(m_tiles[r].m_animal == seed)
				r = qrand() % m_width*m_height;

			m_tiles[r].SetAnimal(seed);
		}
	 }
 }

 //returns false if all stars are full, indicating a level up event;
 bool GameBoard::IncreaseStar()
 {
	 for(int i = 0; i < NUMSTARS; i++)
	 {
		 if(!m_stars[i].m_state)
		 {
			 m_stars[i].SetState(true);
			 return true;
		 }
	 }

	 return false;
 }

 bool GameBoard::DecreaseStar()
 {
	 for(int i = NUMSTARS-1; i >= 0; i--)
	 {
		 if(m_stars[i].m_state)
		 {
			 m_stars[i].SetState(false);
			 return true;
		 }
	 }

	 return false;
 }

 void GameBoard::ResetStars()
 {
	 for(int i = 0; i < NUMSTARS; i++)
	 {
		 m_stars[i].SetState(false);
	 }
 }
