#include "star.h"


Star::Star()
{
	m_emptyStar = new QPixmap;
	m_emptyStar->load(":/images/Resources/Star_Empty.png");

	m_fullStar = new QPixmap;
	if(m_fullStar->load(":/images/Resources/Star_Full.png"))
	{
		SetState(true);
	}

	SetState(false);
}

Star::~Star()
{
	//if(m_emptyStar)
	//	delete m_emptyStar;
	//if(m_fullStar)
	//	delete m_fullStar;

	//m_emptyStar = 0;
	//m_fullStar = 0;
}

void Star::SetSize(int x, int y)
{
	if(m_fullStar && m_fullStar->size().width() == x)
		return;

	QPixmap* p = new QPixmap(m_emptyStar->scaledToWidth(x));
	delete m_emptyStar;
	m_emptyStar = p;

	p = new QPixmap(m_fullStar->scaledToWidth(x));
	delete m_fullStar;
	m_fullStar = p;
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
