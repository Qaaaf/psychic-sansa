#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <qlist.h>

class QGraphicsScene;
class QPixmap;
class Tile;
class GameWindow;
class Star;
class Animal;
class TimeBar;


class GameBoard
{
public:
    GameBoard();
    ~GameBoard();


	void SetupBoard(int tileCountX, int tileCountY);
	void SetBoardGeometry(int x, int y);


    void CreateBoard();
    void ResetBoard();

    void RandomizeBoard();

    void Update(float dt);

	//void OnTileClicked(Tile* tile);

	Tile* GetRandomTile();

	bool GetBoardStable();

	QList<Tile*> GetOpenTiles();
	QList<Tile*> GetTilesOfType(Animal* animal);

	void SetBoardTop();
	void SetBoardBottom();

	void FlipBoard();
	void FlipBoardFaceDown();
	void FlipBoardFaceUp();


	bool IncreaseStar();
	bool DecreaseStar();
	void ResetStars();


	void SeedBoard(Animal* seed);



public:

	int GetTileCount(){return m_tileCountX*m_tileCountY;}

	int m_scrWidth;
	int m_scrHeight;

    int m_playFieldX;
    int m_playFieldY;

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

    TimeBar* m_timeBar;

    QPixmap* pixmap;

    GameWindow* window;

    QGraphicsScene *scene;

private:
	void SetBoardTileXandY(int x, int y);
	void CalculateBoardLayout();
};

#endif // GAMEBOARD_H
