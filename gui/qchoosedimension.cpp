#include <QApplication>
#include"gui/qchoosedimension.h"
#include "gui/qgameboard.h"
#include"gui/qchoosedimensionbutton.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QResizeEvent>

QChooseDimension::QChooseDimension(QWidget *parent) :
    QWidget(parent)
{
    setStyleSheet("QChooseDimensionWindow { background: rgb(237,224,200); }");
    setFixedSize(650,450);
    QVBoxLayout *layout = new QVBoxLayout(this);
    chosen=false;
    QLabel* qchoosedimension = new QLabel("Choose dimension", this);
    qchoosedimension->setStyleSheet("QLabel { color: rgb(119,110,101); font: 40pt; font: bold;} ");
    // reset button
    //QChooseDimensionButton* ChooseDimension1;
    ChooseDimension1 = new QChooseDimensionButton(this,4);
    ChooseDimension2 = new QChooseDimensionButton(this,5);
    ChooseDimension3 = new QChooseDimensionButton(this,6);
    ChooseDimension1->setFixedHeight(50);
    ChooseDimension1->setFixedWidth(100);
    ChooseDimension2->setFixedHeight(50);
    ChooseDimension2->setFixedWidth(100);
    ChooseDimension3->setFixedHeight(50);
    ChooseDimension3->setFixedWidth(100);
    // add game over label to window
    layout->insertWidget(0,qchoosedimension,0,Qt::AlignCenter);
    // add reset button to window
    layout->insertWidget(1,ChooseDimension3,0,Qt::AlignCenter);
    layout->insertWidget(1,ChooseDimension2,0,Qt::AlignCenter);
    layout->insertWidget(1,ChooseDimension1,0,Qt::AlignCenter);
    connect(this->getbutton1(), SIGNAL(clicked()), this, SLOT(setdimention4()));
    connect(this->getbutton2(), SIGNAL(clicked()), this, SLOT(setdimention5()));
    connect(this->getbutton3(), SIGNAL(clicked()), this, SLOT(setdimension6()));
    if(this->chosen==true)
    {
        this->hide();

        QGameBoard board;
        board.show();
        //return a.exec();
    }
}


bool QChooseDimension::QChooseDimension::getchosen() const
{
    return chosen;
}

QChooseDimensionButton* QChooseDimension::getbutton1() const
{
    return ChooseDimension1;
}

QChooseDimensionButton* QChooseDimension::getbutton2() const
{
    return ChooseDimension2;
}

QChooseDimensionButton* QChooseDimension::getbutton3() const
{
    return ChooseDimension3;
}
