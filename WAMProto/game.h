#ifndef GAME_H
#define GAME_H

#include <QObject>

#include "GameBoard.h"
#include <QList>


enum GameType
{
    GAME_WHACKAMOLE,
    GAME_TESTAMOLE,
};

class Animal;
class QTimer;
class Tile;
class Game : public QObject
{
    Q_OBJECT

public:
    Game();

    static Game& I();

    void Update(float dt);

    void Render();


    void playWhackAMole();
    void playTestAMole();

    void startGame();
    void stopGame();

    void updateWhackAMole(float dt);
    void updateTestAMole(float dt);

    void updateStoppingState(float dt);

    void resetGame();

	void SetBoardGeometry(int x, int y);


    enum GameState
    {
        GS_STOPPED,
        GS_STOPPING,
        GS_RUNNING,
        GS_STARTING,
    } m_gameState;

    GameType m_gameType;

    GameBoard* m_board;

	int m_scrWidth;
	int m_scrHeight;

    QList<Animal*> m_animals;
    QList<QTimer*> m_activeTimers;

	void OnTileClicked(Tile* tile);



private:



    int m_level;
    int m_successCounter;

	Animal* m_target;

	enum FLIPMODE
	{
		FM_INSTANT,
		FM_ROWS,
		FM_COLUMNS,
		FM_ROWSSINGLE,
		FM_COLUMNSSINGLE,
		FM_ROWSCOLUMNSSINGLE
	};

    void FlipBoard(FLIPMODE m, bool top = true);
	FLIPMODE m_flipMode;
	int m_flipCount;
	int m_flipColumnCount;
	int m_flipColumnRowsOffsetCount;
	int m_flipInterval;

    void EnsureSuccesPossible();



private slots:
	void RollingFlipTimeOut();
    void DoFlip();

	void StartWAMRound();


};

#endif // GAME_H
