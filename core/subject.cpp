#include "core/subject.h"
#include "core/observer.h"

Subject::Subject()
{
}

void Subject::notifyObservers()
{
    for (Observer* o : observers)
        o->notify();//调用所有observer的notify方法
}

void Subject::registerObserver(Observer* observer)
{
    observers.push_back(observer);//为储存observer指针vector增加一个observer指针
}
