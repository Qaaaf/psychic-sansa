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
    QSoundEffect* m_sound;
    QString m_name;
};

#endif // ANIMAL_H
