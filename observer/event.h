#ifndef EVENT_H
#define EVENT_H

#include <string>
namespace rg
{
class Event
{
public:
    Event();
    Event(std::string type);
    std::string type() const {
        return this->_type;
    }
    void* package;
private:
    std::string _type;
};
}
#endif // EVENT_H
