#ifndef GUIBASE_H
#define GUIBASE_H
#include <SFML/Graphics.hpp>
#include "sizeable.h"
namespace rg {
class Guibase : public Sizeable
{
public:
    Guibase();
    void setSize(sf::Vector2f size);
    sf::Vector2f getSize() const;
    virtual bool isIn(sf::Vector2f mouse) const = 0;
protected:

private:
//    sf::Vector2f size;
};
}

#endif // GUIBASE_H
