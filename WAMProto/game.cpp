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

	QTimer::singleShot(400, this, SLOT(StartWAMRound()));
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
	//m_board->GetRandomTile()->Flip();

	m_board->SetBoardTop();
	m_board->FlipBoard();
}

void Game::RollingFlipTimeOut()
{
	switch (m_flipMode)
	{
	case FM_INSTANT:
		m_flipInterval = 0;
		m_board->FlipBoard();
		m_flipCount = m_board->m_width*m_board->m_height;
		break;
	case FM_ROWS:
		m_flipInterval = 70;
		for(int i = m_flipCount; i < m_flipCount+m_board->m_width; i++)
			m_board->m_tiles[i].Flip();

		m_flipCount += m_board->m_width;
		break;
	case FM_COLUMNS:
		m_flipInterval = 70;
		for(int i = 0; i < m_board->m_height; i++)
			m_board->m_tiles[i*m_board->m_width + m_flipCount].Flip();

		m_flipCount ++;
		if(m_flipCount >= m_board->m_width)
			m_flipCount = m_board->m_width * m_board->m_height;
		break;
	case FM_ROWSSINGLE:
		m_flipInterval = 15;
		m_board->m_tiles[m_flipCount].Flip();
		m_flipCount ++;
		break;
	case FM_COLUMNSSINGLE:
		m_flipInterval = 15;
		m_board->m_tiles[m_flipColumnCount*m_board->m_width + m_flipCount].Flip();

		m_flipColumnCount++;
		if(m_flipColumnCount >= m_board->m_height)
		{
			m_flipColumnCount = 0;
			m_flipCount++;
			if(m_flipCount >= m_board->m_width)
				m_flipCount = m_board->m_width * m_board->m_height;
		}

		break;
	case FM_ROWSCOLUMNSSINGLE:

		break;
	default:
		break;
	}

	if(m_flipCount < (m_board->m_width*m_board->m_height))
		QTimer::singleShot(m_flipInterval, this, SLOT(RollingFlipTimeOut()));
}

void Game::StartWAMRound()
{
	//set target
	int rand = qrand() % m_animals.size();
	m_target = m_animals[rand];
	m_board->m_targetTile->Flip();
	m_board->m_targetTile->SetAnimal(m_target);

	m_board->SeedBoard(m_target, 5);

	FlipBoard(FM_COLUMNSSINGLE);

	//fli
}

void Game::FlipBoard(FLIPMODE m, bool top)
{
    if(top)
        m_board->SetBoardTop();
    else
        m_board->SetBoardBottom();

	m_flipMode = m;
	m_flipCount = 0;
	m_flipColumnCount = 0;
	m_flipColumnRowsOffsetCount = 0;

	RollingFlipTimeOut();
}

void Game::EnsureSuccesPossible()
{
    for(int i = 0; i < m_board->m_width*m_board->m_height; i++)
        if(m_board->m_tiles[i].m_animal == m_target)
            return;
//full flip implement!

    m_board->SeedBoard(m_target, 5);
}

void Game::OnTileClicked(Tile* tile)
{
	if(tile->m_animal == m_target)
	{
		if(!m_board->IncreaseStar())
		{
			//play a victory sound
			m_board->ResetStars();
			m_level++;


            m_board->m_targetTile->Flip(); //flip to back
            QTimer::singleShot(400, this, SLOT(StartWAMRound()));
		}
        else
            EnsureSuccesPossible();
	}
	else
	{
		if(!m_board->DecreaseStar())
		{
			if(m_level)
				m_level--;

			//else gameover?
            // play dramatic sound
            m_board->m_targetTile->Flip(); //flip to back
            QTimer::singleShot(400, this, SLOT(StartWAMRound()));
		}
        else
            EnsureSuccesPossible();
	}

	tile->Flip();
}
