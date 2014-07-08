#include "animal.h"

Animal::Animal(const QString& name)
{
    m_loaded = false;
    m_name = name;

    m_pixmap = new QPixmap;
	m_scaledPixmap = 0;
	m_targetPixmap = 0;
    m_sound = new QSoundEffect;
	QString file = ":/images/Resources/" + name;
    QString soundfile = file + ".wav";
    m_sound->setSource(QUrl::fromLocalFile(soundfile));

    if(m_pixmap->load(file + ".png") && m_sound->isLoaded())
    {
        m_loaded = true;
    }
}


void Animal::SetSize(int x, int y)
{
	if(m_scaledPixmap && m_scaledPixmap->size().width() == x)
		return;

	QPixmap* p = new QPixmap(m_pixmap->scaledToWidth(x));
	delete m_scaledPixmap;
	m_scaledPixmap = p;
}

void Animal::SetTargetSize(int x)
{
	if(m_targetPixmap && m_targetPixmap->size().width() == x)
		return;

	QPixmap* p = new QPixmap(m_pixmap->scaledToWidth(x));
	delete m_targetPixmap;
	m_targetPixmap = p;

}
