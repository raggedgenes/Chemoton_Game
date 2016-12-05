#ifndef LABEL_H
#define LABEL_H
#include "interfaces/sizeable.h"
#include <SFML/Graphics.hpp>

namespace rg
{
class Label : public Sizeable
{
public:
    Label();
    Label(std::string txt);
    void setSize(sf::Vector2f size);
    sf::Vector2f getSize() const;
    bool isIn(sf::Vector2f mouse) {return NULL;}
    sf::Text text;
    sf::Font font;
    void setColor(sf::Color);
    sf::Color getColor() const;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::Color color;
private:
    void init();

};
}

#endif // LABEL_H
