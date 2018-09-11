#ifndef QREPLAYBOARD_H
#define QREPLAYBOARD_H


#include "core/observer.h"
#include "gui/qgamenotice.h"
#include "qgamewin.h"
#include "gui/qbutton.h"
#include <QVector>
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QString>
#include <QDebug>
class QResetButton;
class Game;
class QKeyEvent;
class QNumber;
class QGridLayout;
class QVBoxLayout;
class QLabel;
class Board;

class QReplayBoard : public QWidget
{
public:
    explicit QReplayBoard(QWidget *parent = 0);
    void replay(Game *game1);
   // void stopreplay();

private:
    QVector<QVector<QNumber*> > gui_board;//同core中的board一样，一个二维数组，成员是指向Qnumber的指针
    QVBoxLayout *mainLayout;
    QGridLayout *boardLayout;
    int dimension;//维度
    void drawBoard(Board* board);//绘制界面的函数

};



#endif // QREPLAYBOARD_H
