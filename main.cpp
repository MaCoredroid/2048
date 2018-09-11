#include "gui/mainwindow.h"
#include <QApplication>
#include"gui/qchoosedimension.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "core/board.h"
#include "gui/qgameboard.h"
#include <unistd.h>
#include "gui/qgamenotice.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(NULL));
    QGameBoard board;//创建一个QGameBoard对象
    board.show();//show
    return a.exec();
}
