#ifndef LAYER_H
#define LAYER_H

#include <SFML/Graphics.hpp>
#include "interfaces/sizeable.h"
namespace rg {
class Layer : public Sizeable
{
public:
    Layer();
    ~Layer();
    void addItem(Sizeable &mit);
    void setLayout(char lo);
    void setSize(sf::Vector2f size);
    void autoSize();
    sf::Vector2f getSize() const;
    bool isIn(sf::Vector2f mouse) {return NULL;}
    void handleMouseEvent(sf::Mouse mouse);
    float gap;
    float padding;
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    void resize();
    char layout;
    void positionThis(int index);

    std::vector<Sizeable*> elements;
//    sf::Vector2f position;
};

}


#endif // LAYER_H
