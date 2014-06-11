#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <qlist.h>

class QGraphicsScene;
class QPixmap;
class Tile;
class GameWindow;
class Star;


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

    void OnTileClicked(Tile* tile);

	Tile* GetRandomTile();



    QList<Tile*>& GetOpenTiles();

	void SetBoardTop();
	void SetBoardBottom();



public:
    int m_width;
    int m_height;

    Tile* m_tiles;

	Star* m_stars;

    QPixmap* pixmap;

    GameWindow* window;

    QGraphicsScene *scene;
};

#endif // GAMEBOARD_H
