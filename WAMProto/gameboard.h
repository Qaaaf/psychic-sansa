#ifndef GAMEBOARD_H
#define GAMEBOARD_H

class QGraphicsScene;
class QPixmap;
class Tile;
class GameWindow;





class GameBoard
{
public:
    GameBoard();
    ~GameBoard();

    //static GameBoard& I()
    //{
    //    static GameBoard g;
    //    return g;
    //}

    void SetBoardXY(int x, int y);

    void CreateBoard();
    void ResetBoard();

    void Update(float dt);

    void OnTileClicked(Tile* tile);



public:
    int m_width;
    int m_height;

    Tile* m_tiles;

    QPixmap* pixmap;

    GameWindow* window;

    QGraphicsScene *scene;
};

#endif // GAMEBOARD_H
