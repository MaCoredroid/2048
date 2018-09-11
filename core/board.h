#ifndef BOARD_H
#define BOARD_H

#include "core/subject.h"
#include "core/number.h"
#include <QString>

class Number;
enum Direction { UP, DOWN, LEFT, RIGHT };//枚举四种移动方向
class Board
{
public:

    Board(int dimension=4);//构造维数为dmention的盘子
    Board(const Board& other);//复制另一个board
    ~Board();//析构
    void set();//初始化界面，随机两个格子中有2
    Number* getNumber(int i, int j);//获取格子对应的值
    int getDimension() const { return dimension; }//获取维数
    void move(Direction direction);//移动
    bool full() const;//获取是否已占满
    int getPointsScored() const { return pointsScored; }//获取本轮分数
    bool isCollision() const { return Collision; }//获取本轮是否发生碰撞
    bool movePossible() const ;//获取是否还有移动的机会
    void setNumber(int i,int j,int x);
    Direction gethint(const Board& board);//game对象调用该函数，获取hint的方向
    int dimension;//维数
    Board& operator=(const Board& other);//重载等于运算符
    void easier();//将随机出现的方块全改为2，难度降低


private:
    vector<vector<Number*> > board;//二维数组board，数组元素为指向number类型的指针
    void init();//初始化二维数组，分配空间
    vector<int> freePosition();//获取一个随机的空位置
    bool changed() const;
    bool inboard(int i, int j);//判断是否在边界中
    void moveHorizontally(int i, int j, Direction dir);//横向移动
    void moveVertically(int i, int j, Direction dir);//纵向移动
    void handleCollision(int i, int j);//处理数字碰撞后合并事件
    void prepareForMove();//清空Collision和scoredpoints,并将每一个小块的状态还原为未碰撞
    int pointsScored;//这一次移动获取的分数
    bool Collision;//这一次是否有合并
    double calculate(int depth =1);//计算四个方向移动的分数之和，被hint函数调用
    bool easierflag=0;//将随机出现的方块全改为2，难度降低
};

#endif // BOARD_H
