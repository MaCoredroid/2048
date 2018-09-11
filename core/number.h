#ifndef NUMBER_H
#define NUMBER_H



class Number
{
public:
    Number(int a);//构造
    Number(const Number& other);//复制另一个number
    int getValue();//获取数值
    void upgrade();//碰撞以后乘2
    void setUpgratedThisMove(bool updated);//在这一此移动中值发生变化
    bool getUpgratedThisMove() const;//获取在这一轮中是否发生变化
private:
    int value;//数值
    bool upgratedThisMove;//表征是否发生变化的布尔值
};

#endif // NUMBER_H
