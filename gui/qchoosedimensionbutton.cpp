#include "gui/qchoosedimensionbutton.h"

QChooseDimensionButton::QChooseDimensionButton( QWidget* parent,int dimension) : QLabel(parent)
{
    setText(QString::number(dimension));
    setAlignment(Qt::AlignCenter);
    setStyleSheet("QChooseDimensionButton { color: rgb(119,110,101); font: 40pt; font: bold; }");
}

void QChooseDimensionButton::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}
