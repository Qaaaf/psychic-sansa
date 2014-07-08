#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <qlist.h>

class QGraphicsScene;
class QPixmap;
class Tile;
class GameWindow;
class Star;
class Animal;


class GameBoard
{
public:
    GameBoard();
    ~GameBoard();


	void SetBoardGeometry(int x, int y);
	void SetBoardTileXandY(int x, int y);
	void CalculateBoardLayout();

    void CreateBoard();
    void ResetBoard();

    void RandomizeBoard();

    void Update(float dt);

	//void OnTileClicked(Tile* tile);

	Tile* GetRandomTile();



	QList<Tile*> GetOpenTiles();
	QList<Tile*> GetTilesOfType(Animal* animal);

	void SetBoardTop();
	void SetBoardBottom();

	void FlipBoard();


	bool IncreaseStar();
	bool DecreaseStar();
	void ResetStars();


	void SeedBoard(Animal* seed, int numSeeds);



public:

	int GetTileCount(){return m_tileCountX*m_tileCountY;}

	int m_scrWidth;
	int m_scrHeight;

	float m_ratio;

	int m_tileSizeX;
	int m_tileSizeY;

	int m_tileOffsetX;
	int m_tileOffsetY;

	int m_tileAreaOffset;

	int m_starOffsetX;
	int m_starOffsetY;

	int m_starSizeX;
	int m_starSizeY;

	int m_tileCountX;
	int m_tileCountY;

	Tile** m_tiles;
	Tile* m_targetTile;

	Star** m_stars;

    QPixmap* pixmap;

    GameWindow* window;

    QGraphicsScene *scene;
};

#endif // GAMEBOARD_H
