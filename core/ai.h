#ifndef AI_H
#define AI_H
#include "aiboard.h"
#include <utility>
#include <list>

class Ai{
public:
    static int count;
    Ai(Grid *theGrid);
    ~Ai();
    std::pair<int,double> GetBest(int depth,double alpha,double beta);
private:
    double Evaluate();
    static const double smoothWeight;
    static const double monoWeight;
    static const double emptyWeight;
    static const double maxWeight;
    Grid *grid;
};
#endif // AI_H
