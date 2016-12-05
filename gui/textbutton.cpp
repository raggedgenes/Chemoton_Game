#include "textbutton.h"

using namespace rg;
TextButton::TextButton()
{
}
TextButton::TextButton(std::string txt) : Label(txt) {
    this->hoverColor = sf::Color::White;
}
void TextButton::onHover() {
    text.setColor(this->hoverColor);
}
void TextButton::onOut() {
    text.setColor(this->color);
}
void TextButton::onClick() {
    this->notify_observers(rg::Event("clicked"));
}
bool TextButton::isIn(sf::Vector2f mouse)
{
    sf::FloatRect bound = this->getRGTransform().transformRect(text.getGlobalBounds());
    if (bound.contains(sf::Vector2f((float)mouse.x, (float)mouse.y))) {
        onHover();
        return true;
    } else {
        onOut();
        return false;
    }
}
void TextButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= this->getRGTransform();
    target.draw(text, states);

}
