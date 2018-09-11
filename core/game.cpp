#include "core/game.h"
#include "core/number.h"
#include"core/hint.h"
#include"qdebug.h"


Game::Game(int di)//初始化game对象
{
    dimension=di;
    score = 0;
    step=1;
    highestscore=0;
    board = new Board(dimension);
    ifstream in("score.txt");
    if(!in.is_open())//如果没有已保存的最高分纪录，则创建一个
    {
        ofstream out("score.txt");
        out<<"0"<<endl;
        out.close();
    }
    else//如果有的话，则读取
    {
        int x=0;
        in>>x;
        highestscore=x;
    }
    in.close();
    start();
}
Game::Game(const Game& other)
{
    score=other.getScore();
    highestscore=other.gethighestscore();
    board=other.getGameBoard();
}

Game::~Game()//析构
{
    delete board;
    delete boardtemp;
    for(int i=0;i<step-1;i++)
    {
        delete boardlist[i];
    }
}
bool Game::isGameOver() const//获取是否已经gameOver
{
    return gameOver;
}
Board* Game::getGameBoard() const//获取board
{
    return board;
}
int Game::getScore() const//获取分数
{
    return score;
}
int Game::gethighestscore() const//获取历史最高分
{
    return highestscore;
}

double Game::gettime()//惩罚性措施，超过1000秒重置游戏
{
    double duration = ( std::clock() - starttime ) / (double) CLOCKS_PER_SEC;
    if(duration>=1000)
    {
        gameOver = true;
        notifyObservers();
    }
    return duration;
}
void Game::move(Direction dir)//控制移动的函数
{

    boardlist.resize(step);

    boardlist[step-1]=NULL;

    boardlist[step-1]=new Board(*board);

    board->move(dir);//move


    if (board->isCollision())
    {
        score += board->getPointsScored();//累计分数
        save();
    }
    if (!board->movePossible())
        gameOver = true;//如果不能动了，gameover

    step++;


    notifyObservers();//发起广播
}

void Game::start()//开始游戏，进行一些参数的初始化
{
    step=1;
    starttime = std::clock();
    board->set();
    gameOver = false;
    score = 0;
    boardlist.resize(step);

    boardlist[step-1]=NULL;

    boardlist[step-1]=new Board(*board);

    step++;
}

void Game::save()//当前分数与最高分比较，如超过则保存
{
    ifstream readFile("score.txt");
    int tempscore=0;
    readFile >>tempscore;
    if(score>tempscore)
    {
        highestscore=score;
        ofstream out("score.txt");
        out<<score<<endl;
        out.close();

    }
}



bool Game::isGameWon() const//判断是否赢
{
    for (int i = 0; i < board->getDimension(); ++i)
        for (int j = 0; j < board->getDimension(); ++j)
            if (board->getNumber(i,j) != nullptr && board->getNumber(i,j)->getValue() == WIN_VALUE)//有一个达到了WIN_VALUE
                return true;

    return false;
}

void Game::easier()//降低难度
{
    board->easier();
}
void Game::hint()//获取提示
{
    Direction direction;
    direction=board->gethint(*board);
    move(direction);
}
void Game::record()//以文本文件的形式保存进度
{
    int value=0;
    ofstream outfile;
    outfile.open("laststep.txt");
    if(!outfile.is_open())
        qDebug()<<"Error";
    for (int i = 0; i < dimension; ++i)
        {
            for (int j = 0; j < dimension; ++j)
            {
                if(getGameBoard()->getNumber(i,j)==nullptr)
                {
                    value=0;
                }
                else
                {
                    value=getGameBoard()->getNumber(i,j)->getValue();
                }
                outfile<<value<<endl;
            }
        }
    outfile<<score<<endl;
    outfile.close();
}
void Game::recovery()//读取文本文件形式的进度
{
    ifstream in("laststep.txt");
    if(!in.is_open())
    {
        return;
    }
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            int x=0;
            in>>x;


            getGameBoard()->setNumber(i,j,x);

        }
    }
    int s=0;
    in>>s;
    score=s;
    notifyObservers();//发起广播

}

void Game::drawback()//利用存放Board对象的vector回退操作
{
    if(step<=1)
    {
        return;
    }
    board=new Board(*boardlist[step-2]);
    step--;

    boardlist.resize(step);
    notifyObservers();//发起广播
}
void Game::replay()//利用存放Board对象的vector重放游戏过程
{
    if(step==1||step==2)
    {
        return;
    }
    if(i>=step-2)
     {
      board=new Board(*boardlist[step-2]);
      notifyObservers();//发起广播
      i=0;
     }
     board=new Board(*boardlist[i]);
     i++;
     notifyObservers();//发起广播

}



