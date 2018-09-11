
#ifndef GRID_H
#define GRID_H

#include <list>
#include"core/game.h"
class Grid{
public:
    enum key{
        NONE,
        UP,
        DOWN,
        RIGHT,
        LEFT
    };

    Grid();
    Grid& operator=(const Grid& gird);
    ~Grid();


    void SetLastPress(key k){lastPress = k;}
    int* Combine(int *temp);
    void HandleUp();
    void HandleDown();
    void HandleLeft();
    void HandleRight();
    int* compress(int *t);
    int GetRandom(int range);
    void AddNumber(void);
    int* GetGrid() const ;
    int* GetGridBefore() const;
    int GetScore(){return score;}
    void Copy();
    bool Equal();
    void Undo();
    void Restart();

    int Smoothness();
    int Monotonicity();
    int MaxValue();
    int GetEmptyNumber(){return empty.size();}
    bool IsWin(){return win;}
    bool IsLose(){return lose;}
    bool IsPlayTurn()const{return playerTurn;}
    void ChangePlayTurn(){playerTurn = !playerTurn;}
    bool Move(int direction);
    void InsertTile(int position,int value);
    void RemoveTile(int position);
    std::list<int>& EmptyGrids();
    int EnvaluateInsert(int position,int value);
    bool CheckLose();
    void set(const Game* game);


private:

    std::list<int> empty;
    int number[4][4];
    int *numberOut;
    int *numberOutBefore;
    int numbCopy[4][4];
    int score;
    key lastPress;
    int lastRow;
    int lastLine;
    int totalNumber;
    int lastScore;
    bool playerTurn;
    bool win;
    bool lose;
    void Clear();
    void GetEmpty();


    void Init();
};
#endif // GRID_H
