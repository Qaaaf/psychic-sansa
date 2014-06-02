#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QSpinBox;
QT_END_NAMESPACE

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    SettingsWindow(QWidget *parent);
    ~SettingsWindow();

//    QSize minimumSizeHint() const;
//    QSize sizeHint() const;

private slots:
    void boardChanged();

private:

    QLabel *boardWidthLabel;
    QSpinBox *boardWidthSpinBox;
    QLabel *boardHeightLabel;
    QSpinBox *boardHeightSpinBox;
};

#endif // SETTINGSWINDOW_H
