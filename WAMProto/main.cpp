#include <QApplication>

#include <QtDebug>


#include "gamewindow.h"
#include "settingswindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameWindow w;
    w.show();

    SettingsWindow s(0);
    s.show();


    qDebug() << "Game Started.";

    return a.exec();
}
