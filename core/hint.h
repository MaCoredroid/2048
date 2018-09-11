#ifndef HINT_H
#define HINT_H
#include"core/game.h"
#include"core/board.h"
#include"core/ai.h"
#include"core/aiboard.h"
class Game;
class Hint
{
public:
    Hint(const Game* a);
    Direction gethint();


private:
    Direction hint;
    const Game* game;

};
#endif // HINT_H
