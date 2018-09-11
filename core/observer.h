#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
public:
    Observer();
    virtual void notify() = 0;//纯虚函数
};

#endif // OBSERVER_H
