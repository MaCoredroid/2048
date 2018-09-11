#ifndef QGAMEBOARD_H
#define QGAMEBOARD_H

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
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSoundEffect>

class QResetButton;
class Game;
class QKeyEvent;
class QNumber;
class QGridLayout;
class QVBoxLayout;
class QLabel;

class QGameBoard : public QWidget, public Observer
{
    Q_OBJECT
public:
    explicit QGameBoard(QWidget *parent = 0);
    ~QGameBoard();
    void notify();//状态更新后执行的函数
    Game* game;
    int dimension;//维度


private:


    QVector<QVector<QNumber*> > gui_board;//同core中的board一样，一个二维数组，成员是指向Qnumber的指针
    QVBoxLayout *mainLayout;
    QGridLayout *boardLayout;
    QGridLayout *boardLayout1;
    QLabel *score;//显示内容
    QLabel *highestscore;
    QLabel *time;
    QButton *hint;//显示按钮
    QButton *recovery;
    QButton *reset;
    QButton *replay;
    QButton *colorbtn;
    QButton *drawback;
    QButton *Dimension;
    QButton *Music;
    QButton *Easier;
    QButton *Save;
    QGameNotice gameOver;//提示输赢的对话框
    QGameNotice gameWin;
    void drawBoard();
    int color=1;//更换整体颜色
    QMediaPlayer* player;//背景音乐
    QMediaPlaylist* playlist;
    void Player();
    void Update();
    QSoundEffect effect;//音效
    QSoundEffect effect1;
    QSoundEffect effect2;
    QSoundEffect effect3;

protected:
    void keyPressEvent(QKeyEvent *event);//只允许子类调用



public slots://信号槽
    void resetGame();
    void Hint();
    void Recovery();
    void replaygame();
    void changecolor();
    void Drawback();
    void ChangMusic();
    void easier();
    void drawOther();
    void save();
};

#endif // QGAMEBOARD_H
