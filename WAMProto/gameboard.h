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

    void SetBoardXY(int x, int y);

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
    int m_width;
    int m_height;

    Tile* m_tiles;
	Tile* m_targetTile;

	Star* m_stars;

    QPixmap* pixmap;

    GameWindow* window;

    QGraphicsScene *scene;
};

#endif // GAMEBOARD_H
