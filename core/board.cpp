#include "core/board.h"
#include "core/number.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <QDebug>
#include<QThread>

using namespace std;

Board::Board(int dimension)//dimension:棋盘的格数如4*4
{
    pointsScored = 0;
    Collision = false;
    this->dimension = dimension;
    init();
}

Board::Board(const Board &other)//复制另外一个board二维数组
{
    dimension = other.dimension;
    init();
    for (int i = 0; i < dimension; ++i)
        for (int j = 0; j < dimension; ++j) {
            if (other.board[i][j] == NULL)
                board[i][j] = NULL;
            else
                board[i][j] = new Number(*(other.board[i][j]));
        }
}

void Board::easier()//降低难度，将所有为2的格子改为4
{
    easierflag=1;
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            if((board[i][j]!=nullptr)&&(board[i][j]->getValue()==2))
            {
                board[i][j]=new Number(4);
            }
        }
    }
}

Board& Board::operator=(const Board& other)//重载“=”号
{
    this->dimension = other.dimension;
    board.resize(dimension);//根据维数初始化二位数组的大小
    for (int i = 0; i < dimension; ++i)
        board[i].resize(dimension);
    for (int i = 0; i < dimension; ++i)
        for (int j = 0; j < dimension; ++j)
            board[i][j] = NULL;//初始化为空指针
    for (int i = 0; i < dimension; ++i)
        for (int j = 0; j < dimension; ++j) {
            if (other.board[i][j] == NULL)
                this->board[i][j] = NULL;
            else
                board[i][j] = new Number(*(other.board[i][j]));
        }
    return *this;
}
Board::~Board()//回收棋盘
{
    for (int i = 0 ; i < dimension; ++i)
        for (int j = 0; j < dimension; ++j)
            delete board[i][j];//删除所有格子
}

void Board::init()//初始化储存格子的数组
{
    board.resize(dimension);//根据维数初始化二位数组的大小
    for (int i = 0; i < dimension; ++i)
        board[i].resize(dimension);
    for (int i = 0; i < dimension; ++i)
        for (int j = 0; j < dimension; ++j)
            board[i][j] = NULL;//初始化为空指针
}

vector<int> Board::freePosition()//随机空位置
{
    int a=0;//记录步数
    int b=0;
    vector<int> pos;
    if(full()){
        pos.push_back(-1);
        pos.push_back(-1);
        return pos;
    }//如果full,不随机
    else
    {

        for (int i = 0 ; i < dimension; ++i)
        { for (int j = 0; j < dimension; ++j)
            {
                if(board[i][j]==nullptr)
                {
                    a++;//每多一个空格，步数++
                }

            }
        }
        b=rand() % a;//随机某一步
        for (int i = 0 ; i < dimension; ++i)
        { for (int j = 0; j < dimension; ++j)
            {
                if(board[i][j]==nullptr)
                {
                    if(b==0)//按照相同的顺序回退到那一步
                    {
                        pos.push_back(i);
                        pos.push_back(j);
                        return pos;
                    }
                    else
                    {
                        b--;
                    }
                }


            }
        }

    }
}

bool Board::changed() const//判断整个棋盘是否有碰撞合并
{
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            if((board[i][j]!=nullptr)&&(board[i][j]->getUpgratedThisMove()==true))
            {
                return true;
            }
        }
    }
    return false;
}

void Board::set()//开始新的一局
{
    pointsScored = 0;
    Collision = false;

    for (int i = 0; i < dimension ; ++i) {
        for (int j = 0; j < dimension; ++j) {
            delete board[i][j];
            board[i][j] = nullptr;
        }
    }

    vector<int> start = freePosition();
    board[start[0]][start[1]] = new Number(2);
    start = freePosition();
    board[start[0]][start[1]] = new Number(4);
    easierflag=0;

}

Number* Board::getNumber(int i, int j)//回传一个tile对象
{
    return board[i][j];
}
void Board::setNumber(int i,int j,int x)//改变任意一个位置的值
{
    if(board[i][j]!=NULL)
        delete board[i][j];
    if(x==0)
    {

        board[i][j]=NULL;
    }
    else
    {

        board[i][j]=new Number(x);
    }
}
void Board::move(Direction direction)
{


    prepareForMove();
    switch (direction) {
    case UP:
        for (int i = 0; i < dimension; ++i)//从上到下依次移动
            for (int j = 0; j < dimension; ++j)
                moveVertically(i,j,UP);
        break;
    case DOWN:                             //从下到上依次移动
        for (int i = dimension-1; i >= 0; --i)
            for (int j = 0; j < dimension; ++j)
                moveVertically(i,j,DOWN);
        break;
    case LEFT:                             //从左到右依次移动
        for (int i = 0; i < dimension; ++i)
            for (int j = 0; j < dimension; ++j)
                moveHorizontally(i,j,LEFT);
        break;
    case RIGHT:                            //从右到左依次移动
        for (int i = 0; i < dimension; ++i)
            for (int j = dimension-1; j >= 0; --j)
                moveHorizontally(i,j, RIGHT);
    }
    if (!full())
    {
        if(easierflag==0)
        {
            vector<int> newpos = freePosition();
            int b=rand()%10;
            if(b==0)
            {
                board[newpos[0]][newpos[1]] = new Number(4);
            }
            else
            {
                board[newpos[0]][newpos[1]] = new Number(2);
            }//新生成的数字从2和4中随机
        }
        else
        {
            vector<int> newpos = freePosition();
            board[newpos[0]][newpos[1]] = new Number(4);
        }
    }//放置新的数字，在空格处


}


void Board::prepareForMove()//
{
    Collision = false;//归零发生碰撞的布尔值
    pointsScored= 0;//归零获得的分数
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            if (board[i][j] != NULL) {
                board[i][j]->setUpgratedThisMove(false);//归零每一个小块的个数
            }
        }
    }
}

bool Board::movePossible() const//尝试能否移动
{
    if (full()) {
        Board newBoard(*this);//新创建一个board对象,并复制当前的board
        newBoard.move(UP);//尝试各种方向的移动
        if (newBoard.changed()) return true;
        newBoard.move(DOWN);
        if (newBoard.changed()) return true;
        newBoard.move(LEFT);
        if (newBoard.changed()) return true;
        newBoard.move(RIGHT);
        if (newBoard.changed()) return true;
        return false;
    }
    else {
        return true;
    }
}

double Board::calculate(int depth)//计算每一局面向四个方向移动的平均值
{
    double score=0;
    if(depth==0)
    {
        return 0;
    }
    if(this->movePossible()==0)
    {
        return 0;
    }
    for(int i=depth; i>=1;i--)
    {
        if(this->movePossible())
       {
        Board newBoardup(*this);
        newBoardup.move(UP);
        score+=newBoardup.pointsScored+0.1*newBoardup.calculate(i-1);
        Board newBoarddown(*this);
        newBoarddown.move(DOWN);
        score+=newBoarddown.pointsScored+0.1*newBoarddown.calculate(i-1);
        Board newBoardleft(*this);
        newBoardleft.move(LEFT);
        score+=newBoardleft.pointsScored+0.1*newBoardleft.calculate(i-1);
        Board newBoardright(*this);
        newBoardright.move(RIGHT);
        score+=newBoardright.pointsScored+0.1*newBoardright.calculate(i-1);
        }
    }
    return score;
}

Direction Board::gethint(const Board& board)//利用贪婪算法获取当前局面的较优解
{
    if(board.movePossible()==0)
    {
        return UP;
    }
    Board newBoardup(board);
    newBoardup.move(UP);

    double score=newBoardup.pointsScored+0.1*newBoardup.calculate(4);
    Direction dir=UP;


    Board newBoarddown(board);
    newBoarddown.move(DOWN);
    if(newBoarddown.pointsScored!=0&&((newBoarddown.pointsScored+0.1*newBoarddown.calculate(4))>score))
    {
        dir=DOWN;
    }
    Board newBoardleft(board);
    newBoardleft.move(LEFT);
    if(newBoardleft.pointsScored!=0&&((newBoardleft.pointsScored+0.1*newBoardleft.calculate(4))>score))
    {
        dir=LEFT;
    }
    Board newBoardright(board);
    newBoardright.move(RIGHT);
    if(newBoardright.pointsScored!=0&&((newBoardright.pointsScored+0.1*newBoardright.calculate(4))>score))
    {
        dir=RIGHT;
    }
    return dir;
}

void Board::moveHorizontally(int i, int j, Direction dir)//这个函数处理纵向移动
{
    if (board[i][j] != NULL) {
        bool isCollision = false;
        int newj;
        if (dir == RIGHT)
            newj = j + 1;//向右
        else
            newj = j - 1;//向左
        while (inboard(i,newj) && board[i][newj] == nullptr) {
            if (dir == RIGHT)//碰到空格，继续移动
                newj++;
            else
                newj--;
        }
        if (!inboard(i,newj)) {//出界了，放在边界处
            if (dir == RIGHT)
                board[i][dimension-1] = board[i][j];
            else
                board[i][0] = board[i][j];
        }
        else {//两个value相同并且这一轮没有碰撞
            if (board[i][newj]->getValue() == board[i][j]->getValue() &&
                    !board[i][newj]->getUpgratedThisMove()) {

                isCollision = true;
                handleCollision(i, newj);
            }
            else {
                if (dir == RIGHT)
                    board[i][newj-1] = board[i][j];
                else
                    board[i][newj+1] = board[i][j];
            }
        }
        if ( (dir == RIGHT && newj-1 != j) || (dir == LEFT && newj+1 != j) || isCollision )
            board[i][j] = NULL;

        if (isCollision)
            Collision = true;
    }
}

void Board::moveVertically(int i, int j, Direction dir)//这个函数处理纵向移动
{
    if (board[i][j] != NULL) {
        bool isCollision = false;
        int newi;
        if (dir == UP)
            newi = i - 1;//向上
        else
            newi = i + 1;//向下
        while (inboard(newi,j) && board[newi][j] == NULL) {//碰到的是空格，继续移动
            if (dir == UP)
                newi--;
            else
                newi++;
        }//碰到的是空格，继续前进
        if (!inboard(newi,j)) {
            if (dir == UP)
                board[0][j] = board[i][j];
            else
                board[dimension-1][j] = board[i][j];
        }//出界了，放在第一行/最后一行对应位置
        else {
            if (board[newi][j]->getValue() == board[i][j]->getValue() &&
                    !board[newi][j]->getUpgratedThisMove()) {
                isCollision = true;
                handleCollision(newi, j);
            }//与相同的值碰撞，发生合并
            else {
                if (dir == UP)
                    board[newi+1][j] = board[i][j];
                else
                    board[newi-1][j] = board[i][j];
            }//与不同的值碰撞，不合并
        }
        if ( (dir == UP && newi+1 != i) || (dir == DOWN && newi-1 != i) || isCollision )
            board[i][j] = NULL;//清除原来的值

        if (isCollision)
            Collision = true;//标记这一个动作发生了合并（碰撞）
    }

}

void Board::handleCollision(int i, int j)//这个函数处理发生碰撞的小格子
{
    board[i][j]->upgrade();
    board[i][j]->setUpgratedThisMove(true);//标记这一格的值已经发生了变化
    pointsScored += board[i][j]->getValue();
}

bool Board::full() const//这个函数判断当前的棋盘是否满格
{
    bool full = true;
    for (int i = 0; i < dimension; ++i)
        for (int j = 0; j < dimension; ++j)
            if (board[i][j] == NULL)
                full = false;//有一个位置不为空，便不是全满的状态
    return full;
}

bool Board::inboard(int i, int j)
{
    return (i >= 0 && j >= 0 && i < dimension && j < dimension);//这个函数判断传入的位置是否在界内
}
