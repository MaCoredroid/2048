#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

using namespace std;

class Observer;

class Subject
{
public:
    Subject();
    void notifyObservers();//更新状态并通知观察者
    void registerObserver(Observer* observer);//注册观察者

private:
    vector<Observer*> observers;//存储观察者指针的vector
};

#endif // SUBJECT_H
