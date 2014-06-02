#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

class QGraphicsView;

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    //QSize minimumSizeHint() const;
    //QSize sizeHint() const;

public slots:
void Update();

public:
    //void paintEvent(QPaintEvent *event);
    QGraphicsView *graphicsView;

private:
};

#endif // GAMEWINDOW_H








