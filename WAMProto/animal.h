#ifndef ANIMAL_H
#define ANIMAL_H

#include <QGraphicsPixmapItem>
#include <QSoundEffect>

#include <Qstring>

class Animal
{
public:
    Animal(const QString& name);

    int m_typeId;

    bool m_loaded;

    QPixmap* m_pixmap;
	QPixmap* m_scaledPixmap;
	QPixmap* m_targetPixmap;
    QSoundEffect* m_sound;
    QString m_name;


	void SetSize(int x, int y);
	void SetTargetSize(int x);
};

#endif // ANIMAL_H
