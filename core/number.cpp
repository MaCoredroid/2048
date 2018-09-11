#include "core/number.h"

Number::Number(int a=2){//默认value=2
    value = a;
    upgratedThisMove = false;

}
Number::Number(const Number& other){//复制一个value
    this->value = other.value;

}
int Number::getValue()//获取value的值
{
    return value;
}
void Number::upgrade()//发生碰撞后value*2
{
    value *=2;
}
void Number::setUpgratedThisMove(bool updated)
{
    this->upgratedThisMove = updated;//表明这一个板块发生了碰撞
}
bool Number::getUpgratedThisMove() const
{
    return this->upgratedThisMove;//获取是否发生了碰撞
}
