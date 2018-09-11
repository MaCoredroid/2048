#include"core/hint.h"
#include"core/ai.h"
#include"core/aiboard.h"
#include"core/game.h"
 Hint::Hint(const Game* a)
{
   this->hint=UP;
   this->game=a;

   Grid grid;
   grid.set(this->game);
   Ai ai(&grid);
   int x=0;
   x=ai.GetBest(5,-10000,10000).first;
   switch(x){

   case 1:
       this->hint=UP;
       break;
   case 2:
       this->hint=RIGHT;
       break;
   case 3:
       this->hint=DOWN;
       break;
   case 4:
       this->hint=LEFT;
       break;
   default:
       break;
   }


}
Direction Hint::gethint()
{

    return hint;
}
