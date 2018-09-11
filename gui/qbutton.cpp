#include "gui/qbutton.h"

QButton::QButton( QWidget* parent) : QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
    setStyleSheet("QButton { background-color: rgb(143,122,102); border-radius: 10px; font: bold; color: white; }");
}

void QButton::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}

void QButton::settext(int a)//设置显示的文字内容
{

    switch(a)
    {
        case 0:setText("hint");
        break;
        case 1:setText("reset");
        break;
        case 2:setText("recovery");
        break;
        case 3:setText("replay");
        break;
        case 4:setText("color");
        break;
        case 5:setText("drawback");
        break;
        case 6:setText("music");
        break;
        case 7:setText("easier");
        break;
        case 8:setText("save");
        break;
        default:setText("");
    }

}
