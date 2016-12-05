#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Observer/eventdispatcher.h"

class Controller : public rg::Observer
{
public:
    Controller();
    void notify(rg::Subject *s);
};

#endif // CONTROLLER_H
