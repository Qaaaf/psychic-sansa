#include "game.h"

#include "animal.h"
#include "tile.h"

#include <qtimer.h>

#define FLIPFAST 1200
#define FLIPSLOW 400
#define FLIPSUPERSLOW 100



QPixmap* pDefault;
QPixmap* pScaledDefault;
QPixmap* pTargetDefault;

void LoadDefault()
{
	pDefault = new QPixmap;
	pDefault->load(":/images/Resources/Icon_Back.png");

	pScaledDefault = 0;
	pTargetDefault = 0;
}

QPixmap* Game::GetDefault()
{
	if(pScaledDefault)
		return pScaledDefault;
	else
		return pDefault;
}

QPixmap* Game::GetTargetDefault()
{
	return pTargetDefault;
}

void Game::ScaleDefault(int x, int x2)
{
	delete pScaledDefault;
	pScaledDefault = new QPixmap(pDefault->scaledToWidth(x));
	delete pTargetDefault;
	pTargetDefault = new QPixmap(pDefault->scaledToWidth(x2));
}

Game::Game()
{
	LoadDefault();

	m_animals.clear();
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
	m_flipSpeed = FLIPFAST;

	m_roundTimer = new QTimer(this);
	connect(m_roundTimer, SIGNAL(timeout()), this, SLOT(RoundTimeOut()));
	m_roundTimer->setSingleShot(true);

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

	switch(m_roundState)
	{
	case RS_PLAYING:
		break;
	case RS_READY:
		m_roundTimer->start(10000);
		m_roundState = RS_PLAYING;
		break;
	case RS_UPDATINGBOARDFORPLAYING:
		if(m_board->GetBoardStable())
		{
			StartRound();
		}
		break;
	case RS_UPDATINGBOARDFORREADY:
		if(m_board->GetBoardStable())
		{
			m_roundState = RS_READY;
		}
		break;
	case RS_UPDATINGBOARDFORCONTINUE:
		if(m_board->GetBoardStable())
		{
			if(m_board->m_tiles[0]->FaceUp())
				m_roundState = RS_PLAYING;
			else
			{
				m_board->SeedBoard(m_target);

				m_flipSpeed = FLIPFAST;
				FlipBoard(FM_INSTANT, true);
			}
		}
	default:
		break;
	}
}

void Game::startGame()
{
	m_level = 0;
	m_successCounter = 0;

    m_gameState = GS_RUNNING;

	QTimer::singleShot(400, this, SLOT(StartRound()));
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

void Game::StartRound()
{
	m_board->SetupBoard(m_level+2, m_level+2);
	m_board->ResetStars();

	m_roundState = RS_UPDATINGBOARDFORREADY;

	int rand = qrand() % m_animals.size();
	m_target = m_animals[rand];
	m_board->m_targetTile->Flip();
	m_board->m_targetTile->SetTargetTilePixmap(m_target);

	m_board->SeedBoard(m_target);

	m_flipSpeed = FLIPFAST;
	FlipBoard(FM_COLUMNSSINGLE);
}

void Game::DoFlip()
{
	//m_board->GetRandomTile()->Flip();

	FlipBoard(FM_INSTANT);
}

int Game::GetFlipSpeed()
{
	return m_flipSpeed;
}



void Game::FlipBoard(FLIPMODE m, bool faceUp)
{
	if(m_flipMode != FM_DONE)
		return;

	m_flipTarget = faceUp;
	m_flipMode = m;
	m_flipCount = 0;
	m_flipColumnCount = 0;
	m_flipColumnRowsOffsetCount = 0;

	RollingFlipTimeOut();
}

void Game::EnsureSuccesPossible()
{
	for(int i = 0; i < m_board->GetTileCount(); i++)
		if(m_board->m_tiles[i]->m_animal == m_target && m_board->m_tiles[i]->FaceUp())
            return;

	m_roundState = RS_UPDATINGBOARDFORCONTINUE;
	FlipBoard(FM_INSTANT, false);

}

void Game::OnTileFlipped(Tile* tile)
{
	if(m_flipMode == FM_DONE && m_gameState == GS_RUNNING && m_roundState == RS_PLAYING && m_board->GetBoardStable())
		EnsureSuccesPossible();
}

void Game::OnTileClicked(Tile* tile)
{
	if(m_gameState != GS_RUNNING && m_roundState != RS_PLAYING)
		return;

	tile->Flip();
	if(tile->m_animal == m_target)
	{
		if(!m_board->IncreaseStar())
		{
			//play a victory sound
			m_level++;

            m_board->m_targetTile->Flip(); //flip to back
			m_flipSpeed = FLIPSLOW;
			FlipBoard(FM_INSTANT, false);

			m_roundState = RS_UPDATINGBOARDFORPLAYING;
		}
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
			m_flipSpeed = FLIPSLOW;
			FlipBoard(FM_INSTANT, false);

			m_roundState = RS_UPDATINGBOARDFORPLAYING;
		}
	}
}

void Game::RoundTimeOut()
{
	if(m_roundState != RS_PLAYING)
		return;

	if(m_level)
		m_level--;

	//else gameover?
	// play dramatic sound
	m_board->m_targetTile->Flip(); //flip to back
	m_flipSpeed = FLIPSLOW;
	FlipBoard(FM_INSTANT, false);

	m_roundState = RS_UPDATINGBOARDFORPLAYING;

}

void Game::RollingFlipTimeOut()
{
	switch (m_flipMode)
	{
	case FM_INSTANT:
		m_flipInterval = 0;
		if(m_flipTarget)
			m_board->FlipBoardFaceUp();
		else
			m_board->FlipBoardFaceDown();
		m_flipCount = m_board->GetTileCount();
		break;
	case FM_ROWS:
		m_flipInterval = 70;
		for(int i = m_flipCount; i < m_flipCount+m_board->m_tileCountX; i++)
			m_board->m_tiles[i]->FlipToFace((Tile::FaceState)m_flipTarget);

		m_flipCount += m_board->m_tileCountX;
		break;
	case FM_COLUMNS:
		m_flipInterval = 70;
		for(int i = 0; i < m_board->m_tileCountY; i++)
			m_board->m_tiles[i*m_board->m_tileCountX + m_flipCount]->FlipToFace((Tile::FaceState)m_flipTarget);

		m_flipCount ++;
		if(m_flipCount >= m_board->m_tileCountX)
			m_flipCount = m_board->GetTileCount();
		break;
	case FM_ROWSSINGLE:
		m_flipInterval = 15;
		m_board->m_tiles[m_flipCount]->FlipToFace((Tile::FaceState)m_flipTarget);
		m_flipCount++;
		break;
	case FM_COLUMNSSINGLE:
		m_flipInterval = 15;
		m_board->m_tiles[m_flipColumnCount*m_board->m_tileCountX + m_flipCount]->FlipToFace((Tile::FaceState)m_flipTarget);

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
