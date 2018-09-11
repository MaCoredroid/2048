#ifndef GAME_H
#define GAME_H

#define WIN_VALUE 2048

#include "core/subject.h"
#include "core/board.h"
#include<fstream>
#include<iostream>

#include <cstdio>
#include <ctime>


class Board;
class Game : public Subject
{
public:
    Game(int di);//构造
    Game(const Game& other);//深复制另外一局游戏
    ~Game();//析构
    void start();//开始
    bool isGameOver() const;//获取游戏是否输掉的布尔值
    Board* getGameBoard() const;//获取一个Board对象的引用
    bool isGameWon() const;//获取游戏是否赢
    void move(Direction dir);//移动
    bool won() const ;//获取游戏是否赢的布尔值
    int getScore() const;//获取这一次移动获得的分数
    int gethighestscore() const;//获取最高分（存档中和当前游戏中）
    void hint();//机器智能，提示下一步
    void record();//记录当前的分数和游戏进度
    void recovery();//恢复
    void replay();//回放
    void drawback();//撤回操作
    void easier();//将随机出现的方块全改为2，难度降低
    double gettime();//获取游戏已经进行的时间
private:
    Board* board;//一个board对象的指针
    Board* boardtemp;
    bool gameOver;//是否gameOver的布尔值
    int score;//累计的分数
    int highestscore;//本轮游戏中的最高分数
    void save();//保存进度
    int dimension;//维数
    vector<Board*> boardlist;//用于实现回放和回退功能
    int step;//保存这一局的步数
    int i=0;//replay功能的计数
    std::clock_t starttime;//游戏的开始时间
};

#endif // GAME_H
