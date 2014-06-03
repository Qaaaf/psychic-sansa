#ifndef GAME_H
#define GAME_H

#include "GameBoard.h"

enum GameType
{
    GAME_WHACKAMOLE,
    GAME_TESTAMOLE,
};

class Game
{
public:
    static Game& I()
    {
        static Game g;
        return g;
    }

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

private:
    Game();
};

#endif // GAME_H
