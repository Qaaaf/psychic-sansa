#include "game.h"

Game::Game()
{
    m_board = new GameBoard();
    m_gameState = GS_STOPPED;

    //resetGame();


}

void Game::Update(float dt)
{
    m_board->Update(dt);

    switch (m_gameState)
    {
    case GS_STOPPED:
        break;
    case GS_STOPPING:
        break;
    case GS_STARTING:
        break;
    case GS_RUNNING:
        break;
    default:
        break;
    }
}

void Game::Render()
{
}

void Game::playWhackAMole()
{
    startGame();
}

void Game::playTestAMole()
{
    startGame();
}

void Game::startGame()
{
    m_gameState = GS_STARTING;
}

void Game::stopGame()
{
    m_gameState = GS_STOPPING;
}

void Game::updateWhackAMole(float dt)
{
}
void Game::updateTestAMole(float dt)
{
}

void Game::updateStoppingState(float dt)
{
    resetGame();

}

void Game::resetGame()
{
    m_board->ResetBoard();

    m_gameState = GS_STOPPED;
}
