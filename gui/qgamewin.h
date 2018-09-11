#ifndef QGAMEWINWIN_H
#define QGAMEWINWIN_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QResizeEvent>
class QResetButton;

class QGameWin: public QWidget
{
    Q_OBJECT
public:
    explicit QGameWin(QWidget *parent = 0);

    QResetButton* getResetBtn() const;//获取指向resetbutton的指针，用于信号槽

signals:

public slots:

private:
    QResetButton* reset;//指向resetbutton的指针

};
#endif // QGAMEWINWIN_H
