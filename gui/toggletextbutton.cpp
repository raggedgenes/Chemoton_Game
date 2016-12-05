#include "toggletextbutton.h"
using namespace rg;
ToggleTextButton::ToggleTextButton(std::string txt1, std::string txt2) : TextButton(txt1)
{
    egy = txt1;
    ketto = txt2;
    on = false;
    onColor = sf::Color::Red;
}
void ToggleTextButton::onClick() {
    on = !on;
    if (on) {
        text.setString(ketto);
        text.setColor(onColor);
    } else {
        text.setString(egy);
        text.setColor(color);
    }

    //this->notify_observers(rg::Event("clicked"));
}
void ToggleTextButton::onOut() {
    if (on) {
        text.setColor(onColor);
    } else {
        text.setColor(color);
    }
}
bool ToggleTextButton::isOn() const {
    return on;
}

void ToggleTextButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= this->getRGTransform();
    target.draw(text, states);
}
void ToggleTextButton::setState(bool on) {
    this->on = on;
}
