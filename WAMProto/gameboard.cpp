#include "game.h"
#include "gameboard.h"
#include "tile.h"
#include "star.h"

#include <QPixmap>
#include <QGraphicsScene>

#include <QtDebug>

#include "gamewindow.h"

#include "animal.h"

#define NUMSTARS 3
#define SCOREFIELDSIZE 0.15


GameBoard::GameBoard()
{
    pixmap = new QPixmap;
    pixmap->load("../Resources/Icon_Back.png");

	m_tileCountX = 0;
	m_tileCountY = 0;

	m_scrWidth = 0;
	m_scrHeight = 0;

    m_tiles = 0;
	m_targetTile = 0;
	m_stars = 0;
    window = 0;

    scene = new QGraphicsScene(0);
	scene->setSceneRect(0,0, 0,0);


	m_tileSizeX = 0;
	m_tileSizeY = 0;

	m_tileOffsetX = 0;
	m_tileOffsetY = 0;

	m_tileAreaOffset = 0;

	m_starOffsetX = 0;
	m_starOffsetY = 0;

	m_starSizeX = 0;
	m_starSizeY = 0;
}

GameBoard::~GameBoard()
{
}


void GameBoard::SetBoardTileXandY(int x, int y)
{
	m_tileCountX = x;
	m_tileCountY = y;
}

static int gcd (int a, int b)
{
	return (b == 0) ? a : gcd (b, a%b);
}

void GameBoard::SetBoardGeometry(int x, int y)
{
	scene->setSceneRect(0, 0, x, y);

	m_scrWidth = x;
	m_scrHeight = y;
}

void GameBoard::CalculateBoardLayout()
{
	int scoreFieldX = m_scrWidth*SCOREFIELDSIZE;
	int scoreFieldY = m_scrHeight;

	int playFieldX = m_scrWidth - scoreFieldX;
	int playFieldY = m_scrHeight;


	int tileSizeX = playFieldX / (m_tileCountX+1);
	int tileSizeY = playFieldY / (m_tileCountY+1);

	m_tileSizeY = m_tileSizeX = (tileSizeX < tileSizeY)? tileSizeX : tileSizeY;

	m_tileOffsetX = (playFieldX - (m_tileSizeX*m_tileCountX)) / (m_tileCountX+1);
	m_tileOffsetY = (playFieldY - (m_tileSizeY*m_tileCountY)) / (m_tileCountY+1);

	int starSizeX = scoreFieldX*0.9;
	while(starSizeX*5 > m_scrHeight)
		starSizeX--;

	m_starSizeX = starSizeX;
	m_starSizeY = starSizeX;

	m_starOffsetX = (scoreFieldX - starSizeX) /2;
	m_starOffsetY = (scoreFieldY - (m_starSizeY*4) ) /5;

	m_tileAreaOffset = scoreFieldX;


	m_ratio = m_scrWidth/m_scrHeight;

	CreateBoard();
}

void GameBoard::CreateBoard()
{
	if(m_tileCountX < 1 || m_tileCountY < 1)
        return;


    if(m_tiles)
    {
		scene->clear();
		m_tiles = 0;
		m_stars = 0;
    }

	//if(m_targetTile)
	//	delete m_targetTile;

	for(int i = 0; i<5; i++)
	{
		Game::I().m_animals[i]->SetTargetSize(m_starSizeX);
		Game::I().m_animals[i]->SetSize(m_tileSizeX, m_tileSizeY);
	}

	m_targetTile = new Tile();
	m_targetTile->setAcceptedMouseButtons(false);
	m_targetTile->setPos(m_starOffsetX + m_starSizeX/2, m_starSizeY*3+m_starOffsetY*4 + m_starSizeY/2);
	scene->addItem(m_targetTile);

	m_tiles = new Tile*[GetTileCount()];

	m_stars = new Star*[NUMSTARS];
	for(int i = 0; i < NUMSTARS; i++)
	{
		m_stars[i] = new Star();
		m_stars[i]->setPos(m_starOffsetX, + m_starOffsetY + m_starSizeY*i+m_starOffsetY*i);
		m_stars[i]->SetSize(m_starSizeX, m_starSizeY);
		scene->addItem(m_stars[i]);
	}

	ResetStars();

	for(int y = 0; y < m_tileCountY; y++)
		for(int x = 0; x < m_tileCountX; x++)
        {
			int i = y * m_tileCountX + x;
			m_tiles[i] = new Tile();
			m_tiles[i]->setPos(x*m_tileSizeX+m_tileOffsetX*x + m_tileAreaOffset + m_tileOffsetX + m_tileSizeX/2,
							  y*m_tileSizeY+m_tileOffsetY*y + m_tileSizeY/2 + m_tileOffsetY);

			scene->addItem(m_tiles[i]);
        }

	RandomizeBoard();

    scene->update();
    if(window)
        window->update();
}

void GameBoard::Update(float dt)
{
	for(int i = 0; i < GetTileCount(); i++)
    {
		m_tiles[i]->Update(dt);
    }

	m_targetTile->Update(dt);
}

void GameBoard::ResetBoard()
{
    if(m_tiles)
    {
		for(int i = 0; i < GetTileCount(); i++)
        {
			m_tiles[i]->setFacingToTop();
        }
    }
}

 void GameBoard::RandomizeBoard()
 {
     if(m_tiles)
		 for(int i = 0; i < GetTileCount(); i++)
         {
             int rand = qrand() % (Game::I().m_animals.size());
			 m_tiles[i]->SetAnimal(Game::I().m_animals[rand]);
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
		 for(int i = 0; i < GetTileCount(); i++)
         {
			 if(m_tiles[i]->m_facing == Tile::FS_BOTTOM)
				 list.push_back(m_tiles[i]);
         }

	 return list;
 }

 QList<Tile*> GameBoard::GetTilesOfType(Animal* animal)
 {
	 QList<Tile*> list;

	 if(m_tiles)
		 for(int i = 0; i < GetTileCount(); i++)
		 {
			 if(m_tiles[i]->m_animal == animal)
				 list.push_back(m_tiles[i]);
		 }

	 return list;
 }

 Tile* GameBoard::GetRandomTile()
 {
	 return m_tiles[qrand() % (GetTileCount())];
 }


 void GameBoard::SetBoardTop()
 {
	 ResetBoard();
 }

 void GameBoard::SetBoardBottom()
 {
	 if(m_tiles)
	 {
		 for(int i = 0; i < GetTileCount(); i++)
		 {
			 m_tiles[i]->setFacingToBottom();
		 }
	 }
 }

 void GameBoard::FlipBoard()
 {
	 if(m_tiles)
	 {
		 for(int i = 0; i < GetTileCount(); i++)
		 {
			 m_tiles[i]->Flip();
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
		 for(int i = 0; i < GetTileCount(); i++)
		 {
			 int rand = qrand() % size;
			 m_tiles[i]->SetAnimal(tempanimals[rand]);
		 }

		int r = qrand() % GetTileCount();

		for(int i = 0; i< numSeeds; i++)
		{
			while(m_tiles[r]->m_animal == seed)
				r = qrand() % GetTileCount();

			m_tiles[r]->SetAnimal(seed);
		}
	 }
 }

 //returns false if all stars are full, indicating a level up event;
 bool GameBoard::IncreaseStar()
 {
	 for(int i = 0; i < NUMSTARS; i++)
	 {
		 if(!m_stars[i]->m_state)
		 {
			 m_stars[i]->SetState(true);
			 return true;
		 }
	 }

	 return false;
 }

 bool GameBoard::DecreaseStar()
 {
	 for(int i = NUMSTARS-1; i >= 0; i--)
	 {
		 if(m_stars[i]->m_state)
		 {
			 m_stars[i]->SetState(false);
			 return true;
		 }
	 }

	 return false;
 }

 void GameBoard::ResetStars()
 {
	 for(int i = 0; i < NUMSTARS; i++)
	 {
		 m_stars[i]->SetState(false);
	 }
 }
