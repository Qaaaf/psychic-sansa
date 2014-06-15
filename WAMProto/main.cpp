#include <QApplication>

#include <QtDebug>

#include <QString>




#include "gamewindow.h"
#include "settingswindow.h"

#include "configfile.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	ConfigFile::I().Load("test");

    QJsonObject& json = ConfigFile::I().m_data;

	QJsonObject t;
	t["testString"] = QString("hello");
	t["testDouble"] = 0.12;

	json["player"] = t;

	ConfigFile::I().Save();

    GameWindow w;
    w.show();

    SettingsWindow s(0);
    s.show();


    qDebug() << "Game Started.";

    return a.exec();
}
