#include "gui/qgamenotice.h"
#include "qbutton.h"


QGameNotice::QGameNotice(QWidget *parent) :
    QWidget(parent)
{
}
void QGameNotice::notice(int a)
{
    setStyleSheet("QGameWinWindow { background: rgb(237,224,200); }");
    setFixedSize(425,205);
    QVBoxLayout *layout = new QVBoxLayout(this);
    if(a==0)//根据参数切换显示内容
    {
        QLabel* game = new QLabel("You win!", this);
        game->setStyleSheet("QLabel { color: rgb(119,110,101); font: 40pt; font: bold;} ");
        layout->insertWidget(0,game,0,Qt::AlignCenter);
    }
    else
    {
        QLabel* game = new QLabel("Game over!", this);
        game->setStyleSheet("QLabel { color: rgb(119,110,101); font: 40pt; font: bold;} ");
        layout->insertWidget(0,game,0,Qt::AlignCenter);
    }
    reset = new QButton(this);//新创建一个qresetbutton对象
    reset->setText("Reset");//提示输赢后添加重新开始游戏的按钮
    reset->setFixedHeight(50);
    reset->setFixedWidth(100);

    layout->insertWidget(1,reset,0,Qt::AlignCenter);

}

QButton* QGameNotice::getBtn() const
{
    return reset;
}
