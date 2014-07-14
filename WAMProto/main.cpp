#include <QApplication>

#include <QDesktopWidget>

#include <QtDebug>

#include <QString>




#include "gamewindow.h"
#include "settingswindow.h"
#include "game.h"

#include "configfile.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Q_INIT_RESOURCE(resourcesWAM);

    //ConfigFile::I().Load("test");

    //QJsonObject& json = ConfigFile::I().m_data;

    //QJsonObject t;
    //t["testString"] = QString("hello");
    //t["testDouble"] = 0.12;

    //json["player"] = t;

    //ConfigFile::I().Save();

    GameWindow w;
    w.show();

	//QRect r = a.desktop()->screenGeometry();
	//QRect r2 = a.desktop()->availableGeometry();

	//Game::I().SetBoardGeometry(r.x(), r.y()); //flip because xy are in portrait mode and we need landscape
	Game::I().SetBoardGeometry(1024, 600);
	//Game::I().m_board->SetBoardTileXandY(9,5);
	//Game::I().m_board->CalculateBoardLayout();

	Game::I().startGame();

	//SettingsWindow s(0);
	//s.show();


    qDebug() << "Game Started.";

    return a.exec();
}
