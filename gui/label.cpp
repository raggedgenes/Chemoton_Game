#include "label.h"
#include <iostream>
using namespace rg;
Label::Label() {

}

Label::Label(std::string txt)
{
//    std::cout << "constr label" << std::endl;
    font.loadFromFile("./r/font.ttf");
    color = sf::Color(32,178,170);
    text = sf::Text(txt, font);
//    text.setFont(font); // font is a sf::Font
    text.setCharacterSize(16); // in pixels, not points!
    text.setColor(color);
//    text.setString(txt);
//    init();
}
void Label::setColor(sf::Color color) {
    this->color = color;
    text.setColor(this->color);
}
sf::Color Label::getColor() const {
    return this->color;
}

void Label::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= this->getRGTransform();
    target.draw(text, states);
}

void Label::init() {
}
void Label::setSize(sf::Vector2f size) {
    this->size = sf::Vector2f(text.getLocalBounds().width,(float) text.getCharacterSize());
}
sf::Vector2f Label::getSize() const {
    return sf::Vector2f(text.getLocalBounds().width, (float) text.getCharacterSize());
}

