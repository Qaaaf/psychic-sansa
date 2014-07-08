#include "tile.h"

#include <QPainter>
#include <QPainterPath>

#include <QtWidgets>
#include "QAudio"
#include "QMediaPlayer"

#include "gameboard.h"

#include <QPixmap>
#include <QGraphicsScene>

#include <QtDebug>

#include "gamewindow.h"
#include "animal.h"

#include "Game.h"

QPixmap* pDefault;

void MapPixmaps()
{
	pDefault = new QPixmap;
	pDefault->load(":/Resources/Icon_Back.png");
}

QPixmap* getmap()
{
	return pDefault;
}


bool once = true;
Tile::Tile()
{
	if(once)
		MapPixmaps();
	once = false;

	m_animal = 0;
	m_targetTile = false;

	m_lastpixmap = pDefault;
	m_pixmap = getmap();

	ResetTilesState();

	setTransformOriginPoint(Game::I().m_board->m_tileSizeX/2,Game::I().m_board->m_tileSizeY/2);
}

Tile::~Tile()
{
}

void Tile::SetTargetTilePixmap(Animal* animal)
{
	m_animal = animal;

	m_targetTile = true;

	setTransformOriginPoint(Game::I().m_board->m_starSizeX/2,Game::I().m_board->m_starSizeY/2);
}

void Tile::SetAnimal(Animal* animal)
{
	m_animal = animal;

	SwitchPixmap();
}

void Tile::SwitchPixmap()
{

	if(m_facing == FS_TOP)
		m_pixmap = pDefault;
	else if(!m_targetTile)
		m_pixmap = m_animal->m_scaledPixmap;
	else
		m_pixmap = m_animal->m_targetPixmap;

	setPixmap(*m_pixmap);
}


void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
	QGraphicsPixmapItem::paint(painter, item, widget);
}

QRectF Tile::boundingRect() const
{
	if(m_targetTile)
		return QRectF(0, 0, Game::I().m_board->m_starSizeX, Game::I().m_board->m_starSizeY);

	return QRectF(0, 0, Game::I().m_board->m_tileSizeX, Game::I().m_board->m_tileSizeY);
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsItem::mousePressEvent(event);

	qDebug() << "clickevent";

	Game::I().OnTileClicked(this);
}

void Tile::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsItem::mouseMoveEvent(event);
}

void Tile::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsItem::mouseReleaseEvent(event);
	update();
}


void Tile::Update(float dt)
{
	QTransform m;

	switch(m_state)
	{
	case TS_FLIPPED:
	{
		updateFlippedState(dt);
		break;
	}
	case TS_FLIPPING:
	{
		updateFlippingState(dt);

		break;
	}
	default:
		break;
	}

	m.rotate(m_rotation, Qt::XAxis);

	if(m_targetTile)
		m.translate(-(Game::I().m_board->m_starSizeX/2),-(Game::I().m_board->m_starSizeY/2));
	else
		m.translate(-(Game::I().m_board->m_tileSizeX/2),-(Game::I().m_board->m_tileSizeY/2));
	this->setTransform(m);
}

void Tile::toFlippedState()
{
	m_state = TS_FLIPPED;
}

void Tile::toFlippingState()
{
	if(m_state != TS_FLIPPING)
	{
		m_state = TS_FLIPPING;

		m_turnover = true;

		if(m_facing == FS_TOP);
			//player->play();
	}
}

void Tile::updateFlippedState(float dt)
{
}

void Tile::updateFlippingState(float dt)
{
	if(m_rotation > 90.0 || m_rotation < 0.0)
	{
		if(m_turnover == true)
		{
			if(m_facing == FS_TOP)
				m_facing = FS_BOTTOM;
			else
				m_facing = FS_TOP;


			SwitchPixmap();
			m_turnover = false;
		}
		else
			toFlippedState();

		if(m_rotation > 90)
			m_rotation = 90.0;
		else
			m_rotation = 0.0;

		m_direction = -m_direction;

	}
	else
	{
		m_rotation += 90*dt*15*m_direction;
	}
}


void Tile::ResetTilesState()
{
	m_rotation = 0.0;
	m_direction = 1;
	m_turnover = false;
	m_facing = FS_TOP;

	m_state = TS_FLIPPED;
}

void Tile::setFacingToTop()
{
	ResetTilesState();
	m_facing = FS_TOP;
	SwitchPixmap();
}

void Tile::setFacingToBottom()
{
	ResetTilesState();
	m_facing = FS_BOTTOM;
	SwitchPixmap();
}

void Tile::Flip()
{
	toFlippingState();

	update();
}
