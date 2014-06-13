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


    enum GameState
    {
        GS_STOPPED,
        GS_STOPPING,
        GS_RUNNING,
        GS_STARTING,
    } m_gameState;

    GameType m_gameType;

    GameBoard* m_board;

    QList<Animal*> m_animals;
    QList<QTimer*> m_activeTimers;



private:



    int m_level;
    int m_successCounter;

	Animal* m_target;



private slots:
    void FlipTimeOut();
    void DoFlip();

	void StartWAMRound();


};

#endif // GAME_H
