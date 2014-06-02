#include "settingswindow.h"

#include <QtWidgets>

#include "gameboard.h"

//const int IdRole = Qt::UserRole;

SettingsWindow::SettingsWindow(QWidget* parent) : QWidget(parent)
{
    boardWidthSpinBox = new QSpinBox;
    boardWidthSpinBox->setRange(1, 8000);
    boardWidthSpinBox->setSpecialValueText(tr("1 (minimum!!)"));
    boardWidthSpinBox->setValue(8);

    boardWidthLabel = new QLabel(tr("Board &Width:"));
    boardWidthLabel->setBuddy(boardWidthSpinBox);

    connect(boardWidthSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(boardChanged()));

    boardHeightSpinBox = new QSpinBox;
    boardHeightSpinBox->setRange(1, 8000);
    boardHeightSpinBox->setSpecialValueText(tr("1 (minimum!!)"));
    boardHeightSpinBox->setValue(8);

    boardHeightLabel = new QLabel(tr("Board &Height:"));
    boardHeightLabel->setBuddy(boardHeightSpinBox);

    connect(boardHeightSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(boardChanged()));


    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(boardWidthLabel, 0, 0, Qt::AlignRight);
    mainLayout->addWidget(boardWidthSpinBox, 0, 1);
    mainLayout->addWidget(boardHeightLabel, 1, 0, Qt::AlignRight);
    mainLayout->addWidget(boardHeightSpinBox, 1, 1);

    setLayout(mainLayout);


    setWindowTitle(tr("Game Designer Settings"));


    boardChanged();
}

void SettingsWindow::boardChanged()
{
    int width = boardWidthSpinBox->value();
    int height = boardHeightSpinBox->value();

    //tell gameboard
    GameBoard::I().SetBoardXY(width, height);


}

SettingsWindow::~SettingsWindow()
{
}

//QSize SettingsWindow::minimumSizeHint() const
//{
//    return QSize(100, 100);
//}

//QSize SettingsWindow::sizeHint() const
//{
//    return QSize(400, 400);
//}
