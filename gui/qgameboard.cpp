#include "gui/qgameboard.h"
#include "core/board.h"
#include "core/game.h"
#include "gui/qnumber.h"
#include "core/number.h"
#include "gui/qbutton.h"
#include "windows.h"
#include "QtCore"


QGameBoard::~QGameBoard()
{
    delete game;//析构
}

QGameBoard::QGameBoard(QWidget *parent) : QWidget(parent)
{
    resize(600,850);//控制窗体大小
    int dimension=4;

    mainLayout = new QVBoxLayout();
    setLayout(mainLayout);


    boardLayout = NULL;//初始化Qlabel和QButton的指针
    boardLayout1=NULL;
    score=NULL;
    highestscore=NULL;
    time=NULL;
    hint=NULL;
    recovery=NULL;
    reset=NULL;
    replay=NULL;
    colorbtn=NULL;
    drawback=NULL;
    Music=NULL;
    Easier=NULL;
    Save=NULL;

    game = new Game( dimension);//控制几乘几
    game->registerObserver(this);//注册观察者


    gui_board.resize(game->getGameBoard()->getDimension());//根据维度绘制
    for (int i = 0; i < game->getGameBoard()->getDimension(); ++i)
        gui_board[i].resize(game->getGameBoard()->getDimension());
    for (int i = 0; i < game->getGameBoard()->getDimension(); ++i)
        for (int j = 0; j < game->getGameBoard()->getDimension(); ++j)
            gui_board[i][j] = NULL;//初始化，每一个格子都没有数字
    drawBoard();//绘制空格

    drawOther();
    gameOver.notice(1);//初始化提示Gamewin和Gameover的界面
    gameWin.notice(0);

    setStyleSheet("QGameBoard { background-color: rgb(187,173,160) }");//选择字体
    connect(gameOver.getBtn(), SIGNAL(clicked()), this, SLOT(resetGame()));//在Gamewwin中重新游戏的按钮
    connect(gameWin.getBtn(), SIGNAL(clicked()), this, SLOT(resetGame()));//在Gameover中重新游戏的按钮
    Player();//播放背景音乐
    Update();//开始计时器
    effect.setSource(QUrl::fromLocalFile("D:\\CloudMusic\\soundeffect.wav"));//按钮和数字移动的音效
    effect1.setSource(QUrl::fromLocalFile("D:\\CloudMusic\\soundeffect1.wav"));
    effect2.setSource(QUrl::fromLocalFile("D:\\CloudMusic\\soundeffect2.wav"));
    effect3.setSource(QUrl::fromLocalFile("D:\\CloudMusic\\soundeffect3.wav"));




}

void QGameBoard::Update()//计时器，每一百秒刷新界面，确保时间计数器没有延迟
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(drawOther()));
    timer->start(100);
}

void QGameBoard::Player()//背景音乐播放列表
{

    playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl::fromLocalFile("D:\\CloudMusic\\Alexandre Desplat,The London Symphony Orchestra - Alan.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("D:\\CloudMusic\\王菲 - 寒武纪.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("D:\\CloudMusic\\王菲 - 新房客.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("D:\\CloudMusic\\王菲 - 香奈儿.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("D:\\CloudMusic\\王菲 - 阿修罗.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("D:\\CloudMusic\\王菲 - 彼岸花.mp3"));
    playlist->setCurrentIndex(1);
    player = new QMediaPlayer;
    player->setPlaylist(playlist);
    player->play();

}
void QGameBoard::keyPressEvent(QKeyEvent *event)//方向键的输入进入game对象
{
    switch (event->key()) {
    case Qt::Key_Up:
        game->move(UP);
        break;
    case Qt::Key_Left:
        game->move(LEFT);
        break;
    case Qt::Key_Right:
        game->move(RIGHT);
        break;
    case Qt::Key_Down:
        game->move(DOWN);
        break;
    }
}
void QGameBoard::drawOther()//棋盘下方的按钮，计时器和分数显示
{
    delete boardLayout1;
    boardLayout1 = new QGridLayout();

    delete score;//当前分数
    score = new QLabel(QString("score:%1").arg(game->getScore()));//显示分数
    score->setStyleSheet("QLabel { color: rgb(235,224,214); font: 10pt; }");
    score->setFixedHeight(30);
    boardLayout1->addWidget(score,0,0);

    delete highestscore;//历史最高分
    highestscore = new QLabel(QString("highest score:%1").arg(game->gethighestscore()));//显示分数
    highestscore->setStyleSheet("QLabel { color: rgb(235,224,214); font: 10pt; }");
    highestscore->setFixedHeight(30);
    boardLayout1->addWidget(highestscore,1,0);

    delete time;//这一局开始的时间
    time=new QLabel(QString("Time:%1seconds").arg(game->gettime()));
    time->setStyleSheet("QLabel { color: rgb(235,224,214); font: 10pt; }");
    time->setFixedHeight(30);
    boardLayout1->addWidget(time,2,0);

    delete hint;//获取提示的按钮
    hint = new QButton(this);
    hint->settext(0);
    hint->setFixedWidth(100);
    hint->setFixedHeight(50);
    boardLayout1->addWidget(hint,2,1);

    delete recovery;//恢复之前保存的进度
    recovery = new QButton(this);
    recovery->settext(2);
    recovery->setFixedWidth(100);
    recovery->setFixedHeight(50);
    boardLayout1->addWidget(recovery,2,2);

    delete reset;//重置游戏
    reset = new QButton(this);
    reset->settext(1);
    reset->setFixedWidth(100);
    reset->setFixedHeight(50);
    boardLayout1->addWidget(reset,2,3);

    delete replay;//回放游戏过程
    replay = new QButton(this);
    replay->settext(3);
    replay->setFixedWidth(100);
    replay->setFixedHeight(50);
    boardLayout1->addWidget(replay,3,1);

    delete colorbtn;//换肤按钮
    colorbtn = new QButton(this);
    colorbtn->settext(4);
    colorbtn->setFixedWidth(100);
    colorbtn->setFixedHeight(50);
    boardLayout1->addWidget(colorbtn,3,2);

    delete drawback;//回退操作的按钮
    drawback = new QButton(this);
    drawback->settext(5);
    drawback->setFixedWidth(100);
    drawback->setFixedHeight(50);
    boardLayout1->addWidget(drawback,3,3);

    delete Music;//更换背景音乐的按钮
    Music = new QButton(this);
    Music->settext(6);
    Music->setFixedWidth(100);
    Music->setFixedHeight(50);
    boardLayout1->addWidget(Music,4,1);

    delete Easier;//降低难度的按钮
    Easier = new QButton(this);
    Easier->settext(7);
    Easier->setFixedWidth(100);
    Easier->setFixedHeight(50);
    boardLayout1->addWidget(Easier,4,2);


    delete Save;//保存进度的按钮
    Save = new QButton(this);
    Save->settext(8);
    Save->setFixedWidth(100);
    Save->setFixedHeight(50);
    boardLayout1->addWidget(Save,4,3);



    mainLayout->insertLayout(1, boardLayout1);
    //所有按钮与信号槽的链接
    connect(reset, SIGNAL(clicked()), this, SLOT(resetGame()));
    connect(hint, SIGNAL(clicked()), this, SLOT(Hint()));
    connect(recovery, SIGNAL(clicked()), this, SLOT(Recovery()));
    connect(replay, SIGNAL(clicked()), this, SLOT(replaygame()));
    connect(colorbtn, SIGNAL(clicked()), this, SLOT(changecolor()));
    connect(drawback, SIGNAL(clicked()), this, SLOT(Drawback()));
    connect(Music, SIGNAL(clicked()), this, SLOT(ChangMusic()));
    connect(Easier, SIGNAL(clicked()), this, SLOT(easier()));
    connect(Save, SIGNAL(clicked()), this, SLOT(save()));







}

void QGameBoard::save()//保存进度的按钮
{
    game->record();
    effect3.play();//按钮音效
}

void QGameBoard::ChangMusic()//更换背景音乐的按钮
{
    playlist->next();
    effect3.play();//按钮音效
}

void QGameBoard::easier()//降低难度的按钮
{
    game->easier();
}

void QGameBoard::notify()//接受通知，并作出相应动作
{

    if (game->isGameWon())//拼出2048
    {
        gameWin.show();
        effect1.play();
    }

    else
        score->setText(QString("SCORE: %1").arg(game->getScore()));//显示分数
    if (game->isGameOver())//无法继续进行
    {
        gameOver.show();
        effect2.play();
    }



    drawBoard();//每次更新重新绘制board
    drawOther();
}

void QGameBoard::drawBoard()
{
    effect.play();
    delete boardLayout;
    boardLayout = new QGridLayout();
    for (int i = 0; i < game->getGameBoard()->getDimension(); ++i) {
        for (int j = 0; j < game->getGameBoard()->getDimension(); ++j) {
            delete gui_board[i][j];
            gui_board[i][j] = new QNumber(game->getGameBoard()->getNumber(i,j));//新建Qnumber对象
            boardLayout->addWidget(gui_board[i][j], i, j);
            gui_board[i][j]->draw(color);//调用Qnumber中的绘制
        }
    }
    mainLayout->insertLayout(0, boardLayout);
}

void QGameBoard::Hint()//获取提示的按钮
{
    game->hint();
}

void QGameBoard::changecolor()//换肤按钮
{
    if(color==1)
    {
        color=2;
    }
    else color=1;

    effect3.play();

}

void QGameBoard::Recovery()//恢复之前保存的进度
{
    game->recovery();
}

void QGameBoard::Drawback()//回退操作
{
    game->drawback();
}
void QGameBoard::resetGame()//重新开始游戏
{
    game->start();
    drawBoard();
    drawOther();
    score->setText(QString("SCORE: %1").arg(game->getScore()));
    gameOver.hide();//隐藏窗口
    gameWin.hide();
}

void QGameBoard::replaygame()//回放游戏过程
{
    game->replay();
}





