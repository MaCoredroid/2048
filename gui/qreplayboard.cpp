#include "gui/qreplayboard.h"
#include "core/board.h"
#include "core/game.h"
#include "gui/qnumber.h"
#include "core/number.h"
#include "gui/qbutton.h"
#include <iostream>
#include <thread>
#include <chrono>

QReplayBoard::QReplayBoard(QWidget *parent) : QWidget(parent)
{
    resize(450,450);//控制窗体大小
    int dimension=4;

    mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    boardLayout = NULL;
    gui_board.resize(dimension);//根据维度绘制
    for (int i = 0; i < dimension; ++i)
        gui_board[i].resize(dimension);
    for (int i = 0; i < dimension; ++i)
        for (int j = 0; j < dimension; ++j)
            gui_board[i][j] = NULL;//初始化，每一个格子都没有数字
}

void QReplayBoard::replay(Game *game)
{

    for(int i=0; i<(game->step);i++ )
    {
        drawBoard(game->boardlist[i]);
        std::this_thread::sleep_for (std::chrono::seconds(1));

    }
}

void QReplayBoard::drawBoard(Board* board)
{
    delete boardLayout;
    boardLayout = new QGridLayout();
    for (int i = 0; i < board->dimension; ++i) {
        for (int j = 0; j < board->dimension; ++j) {
            delete gui_board[i][j];
            gui_board[i][j] = new QNumber(board->getNumber(i,j));//新建Qnumber对象
            boardLayout->addWidget(gui_board[i][j], i, j);
            gui_board[i][j]->draw();//调用Qnumber中的绘制
        }
    }
    mainLayout->insertLayout(0, boardLayout);
}



