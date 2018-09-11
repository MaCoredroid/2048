#include "aiboard.h"
#include <QtCore>
#include <math.h>
#include "core/number.h"

Grid::Grid()
     :numberOut(NULL),
      numberOutBefore(NULL),
      score(0),
      lastPress(NONE),
      lastRow(),
      lastLine(),
      totalNumber(0),
      lastScore(0),
      empty(),
      playerTurn(false),
      win(false),
      lose(false)
{
    numberOut = new int[16];
    numberOutBefore = new int[16];
    Clear();
    Init();
}

void Grid::Clear(){
    for(int i = 0; i < 4;i++){
        for(int j = 0;j < 4;j++){
            number[i][j] = 0;
            numbCopy[i][j] = 0;
        }
    }
    score = 0;
}
void Grid::set(const Game* game)
{
   for(int i = 0; i < 4;i++){
        for(int j = 0;j < 4;j++){
            if(game->getGameBoard()->getNumber(i,j)!=NULL)
            number[i][j] = game->getGameBoard()->getNumber(i,j)->getValue();
        }
    }
   for (int i = 0 ; i < 4 ;i++){
       for (int j= 0; j<4 ; j++){
           numberOut[i*4+j] = number[i][j];
       }
   }
   for (int i = 0 ; i < 4 ;i++){
       for (int j= 0; j<4 ; j++){
           numberOutBefore[i*4+j] = numbCopy[i][j];
       }
   }
    score = game-> getScore();
}
void Grid::Init(){
    AddNumber();
    AddNumber();
}

Grid& Grid::operator =(const Grid& grid){
    if(&grid != this){
        const int *temp = grid.GetGrid();
        const int *tempBefore = grid.GetGridBefore();
        if(!grid.IsPlayTurn()){
            ChangePlayTurn();
        }
        for (int i=0 ; i<4 ; i++){
            for(int j=0; j<4; j++){
                this->number[i][j] = temp[i*4+j];
                this->numbCopy[i][j] = tempBefore[i*4+j];
            }
        }
    }
    return *this;
}

Grid::~Grid(){
    if(numberOut != NULL){
        delete [] numberOut;
    }
    if(numberOutBefore != NULL){
        delete [] numberOutBefore;
    }
}

int* Grid::Combine(int *temp){
    lastScore = score;
    compress(temp);
    for(int i=0;i<4;i++){
        if(temp[i]!=0&&temp[i]==temp[i+1]){
            temp[i]=2*temp[i];
            score+=temp[i];
            temp[i+1]=0;
        }
        if(temp[i] >= 2048){
            win = true;
        }
    }
    compress(temp);
    return temp;
}

/*search input array and compress them in fornt several dimension*/
int* Grid::compress(int *t){
    int container[4]={0,0,0,0};
    int turn = 0;
    for(int i=0;i<4;i++){
        if (t[i]!=0){
            container[turn]=t[i];
            turn++;
        }
    }
    for(int i=0;i<4;i++){
        t[i]=container[i];
    }
    return t;
}


void Grid::HandleUp(){
    Copy();
    int temp[4]={0,0,0,0};
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            temp[j]=number[j][i];
        }
        Combine(temp);
        for(int j=0;j<4;j++){
            number[j][i]=temp[j];
        }
    }
}

void Grid::HandleDown(){
    Copy();
    int temp[4]={0,0,0,0};
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            temp[j]=number[3-j][i];
        }
        Combine(temp);
        for(int j=0;j<4;j++){
            number[3-j][i]=temp[j];
        }
    }
}

void Grid::HandleLeft(){
    Copy();
    int temp[4]={0,0,0,0};
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            temp[j]=number[i][j];
        }
        Combine(temp);
        for(int j=0;j<4;j++){
            number[i][j]=temp[j];
        }
    }
}

void Grid::HandleRight(){
    Copy();
    int temp[4]={0,0,0,0};
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            temp[j]=number[i][3-j];
        }
        Combine(temp);
        for(int j=0;j<4;j++){
            number[i][3-j]=temp[j];
        }
    }
}


int Grid::GetRandom(int range){
    if(range == 0){
        exit(1);
    }
    QTime seed =QTime::currentTime();
    qsrand(seed.msec()+seed.second()*1000+seed.msec());
    return qrand()%range;
}

void Grid::AddNumber(void){
    GetEmpty();
    if(empty.size() == 0){
        if(CheckLose()){
            lose = true;
            return;
        }
    }
    int secquence = GetRandom(empty.size());
    std::list<int>::iterator iter =empty.begin();
    for (int i=0;i<secquence;i++){
        iter ++ ;
    }
    int temp = *iter;
    lastRow = temp /10;
    lastLine = temp % 10;
    number[lastRow][lastLine] = (GetRandom(10)==9)?4:2;
    playerTurn = true;
    if(empty.size() == 1){
        if(CheckLose()){
            lose = true;
        }
    }
}

void Grid::Copy(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            numbCopy[i][j] = number[i][j];
        }
    }
}

bool Grid::Equal(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if (numbCopy[i][j] != number[i][j]){
                return false;
            }else if(number[i][j]!= 0){
                totalNumber++;
            }
        }
    }
    return true;
}

void Grid::Undo(){
    score  = lastScore;
    lose = false;
    for(int i =0;i<4;i++){
        for(int j=0;j<4;j++){
            number[i][j] = numbCopy[i][j];
        }
    }
}

int* Grid::GetGrid() const{
    for (int i = 0 ; i < 4 ;i++){
        for (int j= 0; j<4 ; j++){
            numberOut[i*4+j] = number[i][j];
        }
    }
    return numberOut;
}

int* Grid::GetGridBefore() const{
    for (int i = 0 ; i < 4 ;i++){
        for (int j= 0; j<4 ; j++){
            numberOutBefore[i*4+j] = numbCopy[i][j];
        }
    }
    return numberOutBefore;
}

void Grid::Restart(){
    Clear();
    Init();
}

void Grid::GetEmpty(){
    empty.clear();
    for(int i=0;i<4;i++){
        for(int j = 0;j<4;j++){
            if(number[i][j] == 0){
                empty.push_back(i*10+j);
            }
        }
    }
}

std::list<int>& Grid::EmptyGrids(){
    GetEmpty();
    return empty;
}

int Grid::Smoothness(){
    int smoothness = 0;
    int value = 0;
    int targetValue = 0;

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            value = (number[i][j] ==0?0:( log(number[i][j])/log(2) ) );
            //in row
            for(int x=j+1;x<4;x++){
                if(number[i][x] != 0){
                    targetValue = (number[i][x]==0?0:( log(number[i][x])/log(2) ));
                    smoothness -= abs(value - targetValue);
                    break;
                }
            }
            //in line
            for(int x=i+1;x<4;x++){
                if(number[x][j] != 0){
                    targetValue = (number[x][j] == 0?0:( log(number[x][j])/log(2) ));
                    smoothness -= abs(value - targetValue);
                    break;
                }
            }
        }
    }
    return smoothness;
}

int Grid::Monotonicity(){
    int monotonicity=0;
    int mono1 = 0;
    int mono2 = 0;
    int value = 0;
    int targetValue = 0;
    for (int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            value = number[i][j] == 0?0:(log(number[i][j])/log(2));
            for(int x=j+1;x<4;x++){
                if(number[i][x] != 0){
                    targetValue = log(number[i][x])/log(2);
                }else if(x = 3){
                    targetValue = 0 ;
                }else{
                    continue;
                }

                if(value > targetValue){
                    mono1 += targetValue - value;
                }else{
                    mono2 += value - targetValue;
                }
                j = x-1;
                break;
            }
        }
    }
    monotonicity += mono1>mono2? mono1:mono2;

    for (int j=0;j<4;j++){
        for(int i=0;i<4;i++){
            value = number[i][j] == 0?0:(log(number[i][j])/log(2));
            for(int x=i+1;x<4;x++){
                if(number[x][j] != 0){
                    targetValue = log(number[x][j])/log(2);
                }else if(x = 3){
                    targetValue = 0 ;
                }else{
                    continue;
                }

                if(value > targetValue){
                    mono1 += targetValue - value;
                }else{
                    mono2 += value - targetValue;
                }
                i = x-1;
                break;
            }
        }
    }
    monotonicity += mono1>mono2? mono1:mono2;

    return monotonicity;
}


int Grid::MaxValue(){
    int temp = 0;
    for(int i=0;i<4;i++){
        for(int j = 0;j<4;j++){
            if(number[i][j] > temp){
                temp = number[i][j];
            }
        }
    }
    return temp;
}

bool Grid::Move(int direction){
    switch(direction){
    case 1:
        HandleUp();
        break;
    case 2:
        HandleRight();
        break;
    case 3:
        HandleDown();
        break;
    case 4:
        HandleLeft();
        break;
    }
    return !Equal();
}

void Grid::InsertTile(int position, int value){
    if(number[position/10][position%10] == 0 ){
        number[position/10][position%10] = value;
    }else{
        exit(1);
    }
}

int Grid::EnvaluateInsert(int position,int value){
    int x = position/10;
    int y = position%10;
    int temp = 9999;//init it big enough


    //up
    for(int i=x ; i>0 ; i--){
        if(number[i][y] != 0){
            if(abs( (number[i][y] - value)) < temp ){
                temp = abs((number[i][y] - value));
            }
            break;
        }
    }
    //down
    for(int i=x ; i<4 ; i++){
        if(number[i][y] != 0){
            if(abs( (number[i][y] - value)) < temp ){
                temp = abs((number[i][y] - value));
            }
            break;
        }
    }
    //left
    for(int i=y ; i>0 ; i--){
        if(number[x][i] != 0){
            if(abs( (number[x][i] - value)) < temp ){
                temp = abs((number[x][i] - value));
            }
            break;
        }
    }
    //right
    for(int i=y ; i<4 ; i++){
        if(number[x][i] != 0){
            if(abs( (number[x][i] - value)) < temp ){
                temp = abs((number[x][i] - value));
            }
            break;
        }
    }
    return temp==9999?0:temp;
}


void Grid::RemoveTile(int position){
        number[position/10][position%10] = 0;
}

bool Grid::CheckLose(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(number[i][j] == 0){
                return false;
            }
            if(i == 3 && j!=3){
                if(number[i][j] == number[i][j+1]){
                    return false;
                }
            }else if(j == 3){
                if(number[i+1][j] == number[i][j]){
                    return false;
                }
            }else{
                if(number[i][j] == number[i][j+1] ||
                        number[i+1][j] == number[i][j]){
                    return false;
                }
            }
        }
    }
    lose = true;
    return true;
}
