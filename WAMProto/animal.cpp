#include "animal.h"

Animal::Animal(const QString& name)
{
    m_loaded = false;
    m_name = name;

    m_pixmap = new QPixmap;
    m_sound = new QSoundEffect;
    QString file = "../Resources/" + name;
    QString soundfile = file + ".wav";
    m_sound->setSource(QUrl::fromLocalFile(soundfile));

    if(m_pixmap->load(file + ".png") && m_sound->isLoaded())
    {
        m_loaded = true;
    }
}
