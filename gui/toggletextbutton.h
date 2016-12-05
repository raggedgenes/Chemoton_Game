#ifndef TOGGLETEXTBUTTON_H
#define TOGGLETEXTBUTTON_H
#include "textbutton.h"
#include <string>
namespace rg {
class ToggleTextButton : public TextButton
{
public:
    explicit ToggleTextButton(std::string txt1, std::string txt2);
    void onClick();
    bool isOn() const;
    void setState(bool on);
//    void onHover();
    void onOut();
    sf::Color onColor;
private:
    bool on;
    std::string egy;
    std::string ketto;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
}
#endif // TOGGLETEXTBUTTON_H
