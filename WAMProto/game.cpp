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
    m_roundState = RS_READY;
    m_screenState = SS_GAMESCREEN;
    m_flipMode = FM_DONE;

	//playTestAMole();

	//resetGame();
}

Game& Game::I()
{
	static Game g;
	return g;
}

void Game::SetBoardGeometry(int x, int y)
{
	m_scrWidth = x;
	m_scrHeight = y;

	m_board->SetBoardGeometry(x, y);
}


void Game::Update(float dt)
{
    switch(m_screenState)
    {
    case SS_GAMESCREEN:
        switch (m_gameState)
        {
        case GS_STOPPED:
            break;
        case GS_RUNNING:
            UpdateGameRunning(dt);

            break;
        default:
            break;
        }
        break;
    case SS_MAINMENU:
        break;
    case SS_OPTIONS:
        break;
    default:
        break;

    }
}

void Game::UpdateGameRunning(float dt)
{
    m_board->Update(dt);
}

void Game::playWhackAMole()
{
	startGame();


}

void Game::playTestAMole()
{
	//m_board->SetBoardXY(9, 5);

	startGame();

    QTimer::singleShot(400, this, SLOT(StartRound()));
}

void Game::startGame()
{
	m_level = 0;
	m_successCounter = 0;

    m_gameState = GS_RUNNING;
}

void Game::stopGame()
{
    m_gameState = GS_STOPPED;
}

void Game::resetGame()
{
	m_level = 0;
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
		m_flipCount = m_board->GetTileCount();
		break;
	case FM_ROWS:
		m_flipInterval = 70;
		for(int i = m_flipCount; i < m_flipCount+m_board->m_tileCountX; i++)
			m_board->m_tiles[i]->Flip();

		m_flipCount += m_board->m_tileCountX;
		break;
	case FM_COLUMNS:
		m_flipInterval = 70;
		for(int i = 0; i < m_board->m_tileCountY; i++)
			m_board->m_tiles[i*m_board->m_tileCountX + m_flipCount]->Flip();

		m_flipCount ++;
		if(m_flipCount >= m_board->m_tileCountX)
			m_flipCount = m_board->GetTileCount();
		break;
	case FM_ROWSSINGLE:
		m_flipInterval = 15;
		m_board->m_tiles[m_flipCount]->Flip();
		m_flipCount ++;
		break;
	case FM_COLUMNSSINGLE:
		m_flipInterval = 15;
		m_board->m_tiles[m_flipColumnCount*m_board->m_tileCountX + m_flipCount]->Flip();

		m_flipColumnCount++;
		if(m_flipColumnCount >= m_board->m_tileCountY)
		{
			m_flipColumnCount = 0;
			m_flipCount++;
			if(m_flipCount >= m_board->m_tileCountX)
				m_flipCount = m_board->GetTileCount();
		}

		break;
	case FM_ROWSCOLUMNSSINGLE:

		break;
	default:
		break;
	}

	if(m_flipCount < m_board->GetTileCount())
		QTimer::singleShot(m_flipInterval, this, SLOT(RollingFlipTimeOut()));
    else
        m_flipMode = FM_DONE;
}

void Game::StartRound()
{
	//set target
	int rand = qrand() % m_animals.size();
	m_target = m_animals[rand];
	m_board->m_targetTile->Flip();
	m_board->m_targetTile->SetTargetTilePixmap(m_target);

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
	for(int i = 0; i < m_board->GetTileCount(); i++)
		if(m_board->m_tiles[i]->m_animal == m_target)
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

			m_board->SetBoardTileXandY(m_level+2, m_level+2);
			m_board->CalculateBoardLayout();
            QTimer::singleShot(400, this, SLOT(StartRound()));
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
            QTimer::singleShot(400, this, SLOT(StartRound()));
		}
        else
            EnsureSuccesPossible();
	}

	tile->Flip();
}
