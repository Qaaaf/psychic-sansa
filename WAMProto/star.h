#ifndef STAR_H
#define STAR_H

#include <QGraphicsPixmapItem>

class Star : public QGraphicsPixmapItem
{
public:
	Star();
	~Star();

	QPixmap* m_emptyStar;
	QPixmap* m_fullStar;

	bool m_state;

	void SetState(bool state);

    void SetSize(int x);


	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
};

#endif // STAR_H
