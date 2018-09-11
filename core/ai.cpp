#include"ai.h"
#include<math.h>

const double Ai::smoothWeight = 1.0;
const double Ai::monoWeight = 1.0;
const double Ai::emptyWeight = 2.7;
const double Ai::maxWeight = 1.0;

int Ai::count = 20;

Ai::Ai(Grid *theGrid){
    grid = theGrid;
}

Ai::~Ai(){}


double Ai::Evaluate(){
    double temp1 = grid->Smoothness() * smoothWeight;
    double temp2 = grid->Monotonicity() * monoWeight;
    double temp3 = log(grid->GetEmptyNumber()) * emptyWeight;
    double temp4 = grid->MaxValue() * maxWeight;

    return grid->Smoothness() * smoothWeight
            +grid->Monotonicity() * monoWeight
            +log(grid->GetEmptyNumber()) * emptyWeight
            +grid->MaxValue() * maxWeight;
}

std::pair<int,double>
Ai::GetBest(int depth,double alpha,double beta){
    int move = 0;
    double score = 0;

    std::pair<int,int> resault;

    score = alpha;
    for (int dir = 1 ; dir<=4 ; dir++){
        Grid temp;
        temp = *grid;
        if(temp.Move(dir)){
            temp.ChangePlayTurn();
            if( temp.IsWin()){
                return std::make_pair(dir,100000);
            }
            if(depth == 0){
                resault = std::make_pair(dir,Evaluate());
            }else{
                Ai newai(&temp);
                resault = newai.GetBest(depth-1,score,beta);
            }
            if (resault.second > score) {
                score = resault.second;
                move = resault.first;
                move = dir;
            }
            if (score > beta) {
                return std::make_pair(move,beta);
            }
        }
    }

    return std::make_pair(move,score);
}

