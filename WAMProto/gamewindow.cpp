#include "gamewindow.h"

#include <QPainter>
#include <QGraphicsView>
#include <QTimer>

#include "game.h"
#include "tile.h"

#include <QHBoxLayout>


GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent)
{
    Game::I().m_board->window = this;

    //QWidget* w = new QWidget;
    //w->resize(1000,1000);

    graphicsView = new QGraphicsView(this);
    graphicsView->setRenderHint(QPainter::Antialiasing, false);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    graphicsView->setInteractive(true);

    graphicsView->setScene(Game::I().m_board->scene);

    QMatrix matrix;
    matrix.reset();

    graphicsView->setMatrix(matrix);


    setCentralWidget(graphicsView);


    QTimer *timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    timer->start(20);
}

GameWindow::~GameWindow()
{
}

void GameWindow::Update()
{
    Game::I().Update(1.f/50.f);
}
