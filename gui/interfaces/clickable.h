#ifndef CLICKABLE_H
#define CLICKABLE_H
#include <SFML/Graphics.hpp>
#include "../../observer/eventdispatcher.h"

namespace rg {
class Clickable : public Subject
{
public:
    Clickable();
    virtual void onHover() = 0;
    virtual void onOut() = 0;
    virtual void onClick() = 0;
};
}


#endif // CLICKABLE_H
