#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H
#include <SFML/Graphics.hpp>
#include "interfaces/clickable.h"
#include "label.h"
namespace rg {
class TextButton : public Clickable, public Label
{
public:
    TextButton();
    TextButton(std::string txt);
    void onHover();
    void onOut();
    void onClick();
    bool isIn(sf::Vector2f mouse);
    sf::Color hoverColor;
//    void setSize(sf::Vector2f size);
//    sf::Vector2f getSize() const;
//private:
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

};
}


#endif // TEXTBUTTON_H
