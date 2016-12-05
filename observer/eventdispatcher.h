#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <vector>
#include <typeinfo>
#include <string>
#include "event.h"
#include <functional>


namespace rg
{
class Subject;

typedef struct Eventmap Eventmap;

class Observer
{
public:
    virtual void notify(rg::Event e, Subject* self) = 0;
    virtual ~Observer() {}
};

struct Eventmap{
    rg::Event event;
    Observer* obs;
    Eventmap(rg::Event e, Observer* obs) {
        event = e;
        this->obs = obs;
    }
};

class Subject
{
    std::vector<Eventmap> observers;
protected:
    void notify_observers(rg::Event e)
    {
        std::vector<Eventmap>::iterator iter;
        for (iter = observers.begin(); iter != observers.end(); ++iter)
            if (e.type() == ((Eventmap)(*iter)).event.type()) (*iter).obs->notify(e, this);
    }

public:
    virtual ~Subject() {}
    void register_observer(rg::Event event, Observer* o)
    {
        observers.push_back(Eventmap(event, o));
    }
    void unregister_observer(rg::Event e, Observer* obs) {
        std::vector<Eventmap>::iterator iter;
        for (iter = observers.begin(); iter != observers.end(); ++iter)
            if (e.type() == ((Eventmap)(*iter)).event.type() && ((Eventmap)(*iter)).obs == obs) observers.erase(iter, iter+1);
    }
    int id;
};
}
#endif // EVENTDISPATCHER_H
