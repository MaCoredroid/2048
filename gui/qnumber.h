#ifndef QNUMBER_H
#define QNUMBER_H

#include <QLabel>

class Number;

class QNumber : public QLabel
{
    Q_OBJECT
public:
    QNumber(Number* number);//传入一个指向number对象的指针

    void draw(int i=1);//绘制界面
private:
    Number* number;

signals:

public slots:

};

#endif // QNUMBER_H
