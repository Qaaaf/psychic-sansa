#include "star.h"


Star::Star()
{
	m_emptyStar = new QPixmap;
	m_emptyStar->load("../Resources/Star_Empty.png");

	m_fullStar = new QPixmap;
	if(m_fullStar->load("../Resources/Star_Full.png"))
	{
		SetState(true);
	}

	SetState(false);
}

Star::~Star()
{
	if(Star::m_emptyStar)
		delete m_emptyStar;
	if(m_fullStar)
		delete m_fullStar;

	m_emptyStar = 0;
	m_fullStar = 0;
}

void Star::SetState(bool state)
{
	m_state = state;
	if(state)
		setPixmap(*m_fullStar);
	else
		setPixmap(*m_emptyStar);

	update();
}

QRectF Star::boundingRect() const
{
	return QRectF(0, 0, 256, 256);
}

void Star::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
	QGraphicsPixmapItem::paint(painter, item, widget);
}
