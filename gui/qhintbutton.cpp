#include"gui/qhintbutton.h"
QButton::QHintButton( QWidget* parent) : QLabel(parent)
{
    setText("Hint");
    setAlignment(Qt::AlignCenter);
    setStyleSheet("QHintButton { background-color: rgb(143,122,102); border-radius: 10px; font: bold; color: white; }");
}

void QHintButton::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}
