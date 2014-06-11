#include "game.h"

#include "animal.h"

#include <qtimer.h>

#include "tile.h"


Game::Game()
{
	m_animals.clear();
	m_activeTimers.clear();
	for(int i = 0; i<5; i++)
	{
		QString file = "Icon_" + QString::number(i);
		m_animals.push_back(new Animal(file));
	}

	m_board = new GameBoard();
	m_gameState = GS_STOPPED;

	playTestAMole();

	//resetGame();
}

Game& Game::I()
{
	static Game g;
	return g;
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

	QTimer *timer = new QTimer;
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(DoFlip()));
	timer->start(200);

	m_activeTimers.push_back(timer);
}

void Game::startGame()
{
	m_level = 0;
	m_successCounter = 0;

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

void Game::DoFlip()
{
	m_board->GetRandomTile()->Flip();
}

void Game::FlipTimeOut()
{
}
