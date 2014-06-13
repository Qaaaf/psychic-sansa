#include <QApplication>

#include <QtDebug>


#include "gamewindow.h"
#include "settingswindow.h"

#include "configfile.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ConfigFile::I().Load(QString("test"));

    QJsonObject& json = ConfigFile::I().m_data;

    QJsonObject playerObject;
    mPlayer.write(playerObject);
    json["player"] = playerObject;

    QJsonArray levelArray;
    foreach (const Level level, mLevels) {
        QJsonObject levelObject;
        level.write(levelObject);
        levelArray.append(levelObject);
    }
    json["levels"] = levelArray;


    ConfigFile::I().

    GameWindow w;
    w.show();

    SettingsWindow s(0);
    s.show();


    qDebug() << "Game Started.";

    return a.exec();
}
