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
class QPixmap;
class Game : public QObject
{
    Q_OBJECT

public:

    Game();

    static Game& I();

    void Update(float dt);
    void UpdateGameRunning(float dt);

    void playTestAMole();

    void startGame();
    void stopGame();

    void resetGame();

	void SetBoardGeometry(int x, int y);

	QPixmap* GetDefault();
	QPixmap* GetTargetDefault();
	void ScaleDefault(int x, int x2);


	int GetFlipSpeed();
	int m_flipSpeed;


    enum GameState
    {
        GS_STOPPED,
        GS_RUNNING,
    } m_gameState;

    enum ScreenState
    {
        SS_MAINMENU,
        SS_GAMESCREEN,
        SS_OPTIONS,
    } m_screenState;

    enum RoundState
    {
        RS_PLAYING,
		RS_UPDATINGBOARDFORREADY,
		RS_UPDATINGBOARDFORPLAYING,
		RS_UPDATINGBOARDFORCONTINUE,
        RS_READY,
    } m_roundState;

    GameType m_gameType;

    GameBoard* m_board;

	int m_scrWidth;
	int m_scrHeight;

    QList<Animal*> m_animals;

	QTimer* m_roundTimer;

	void OnTileClicked(Tile* tile);
	void OnTileFlipped(Tile* tile);

private:

    int m_level;
    int m_successCounter;

	Animal* m_target;

	enum FLIPMODE
	{
        FM_DONE,
		FM_INSTANT,
		FM_ROWS,
		FM_COLUMNS,
		FM_ROWSSINGLE,
		FM_COLUMNSSINGLE,
		FM_ROWSCOLUMNSSINGLE
	};

	void FlipBoard(FLIPMODE m, bool faceUp = true);
	FLIPMODE m_flipMode;
	int m_flipCount;
	int m_flipColumnCount;
	int m_flipColumnRowsOffsetCount;
	int m_flipInterval;
	bool m_flipTarget;

    void EnsureSuccesPossible();



private slots:
	void RollingFlipTimeOut();
    void DoFlip();

    void StartRound();

	void RoundTimeOut();


};

#endif // GAME_H
