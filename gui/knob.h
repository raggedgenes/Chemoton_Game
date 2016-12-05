#ifndef KNOB_H
#define KNOB_H
#include "interfaces/sizeable.h"
#include "SFML/Graphics.hpp"
#include "label.h"

namespace rg {
class Knob : public Sizeable
{
public:
    explicit Knob(std::string txt, bool exp, sf::Font &font);
    void setSize(sf::Vector2f size);
    sf::Vector2f getSize() const;
    bool isIn(sf::Vector2f mouse);
    void slide(float s);
    void updateNumeric();
    void setValue(double v);
    double getValue() const;
    double min;
    double max;
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::CircleShape kor;
    sf::Text label;
private:
    void setup();
//    float value;
    float width;
    float height;
    bool exponential;
    float currposition;
    sf::VertexArray vonal;
    std::string txt;
    sf::Color color;
//    sf::Font font;
};
}
#endif // KNOB_H
