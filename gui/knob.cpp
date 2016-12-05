#include "knob.h"
#include <cmath>
#include <iostream>
#include <sstream>


using namespace rg;
Knob::Knob(std::string txt, bool exp, sf::Font &font) {
//    std::cout <<"hiba: " << txt << std::endl;
    color = sf::Color(32,178,170);
    exponential = exp;
//    font.loadFromFile("./r/font.ttf");
    label = sf::Text(txt, font);
//    label.setFont(*font);
    label.setCharacterSize(16); // in pixels, not points!
    label.setColor(color);
    this->txt = txt;
//    std::cout << "knob1" << std::endl;
    setup();
//    label.setString(txt);
}
void Knob::setup() {
    width = 160.f;
    height = 40.f;
    currposition = 0.f;
    min = 0;
    max = 99;
    kor = sf::CircleShape(10.f);
    kor.setPosition(0.f, height/2);
    kor.setFillColor(sf::Color::Black);
    kor.setOutlineColor(color);
    kor.setOutlineThickness(2.f);

    vonal = sf::VertexArray(sf::LinesStrip,4);
    vonal[0].position = sf::Vector2f(0.f, 29.f);
    vonal[1].position = sf::Vector2f(width, 29.f);
    vonal[2].position = sf::Vector2f(width, 31.f);
    vonal[3].position = sf::Vector2f(0.f, 31.f);
//    vonal[4].position = sf::Vector2f(0.f, 29.f);
}
void Knob::setSize(sf::Vector2f size) {
    this->size = sf::Vector2f(width, height);
}
sf::Vector2f Knob::getSize() const {
    return this->size;
}
bool Knob::isIn(sf::Vector2f mouse)
{
    sf::FloatRect bound = this->getRGTransform().transformRect(sf::FloatRect(0.f,0.f,width,height));
    if (bound.contains(sf::Vector2f((float)mouse.x, (float)mouse.y))) {
        return true;
    } else {
        return false;
    }
}
void Knob::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= this->getRGTransform();
    target.draw(label, states);
    target.draw(vonal, states);
    target.draw(kor, states);
}

void Knob::slide(float s) {
    //sf::FloatRect bound = this->getRGTransform().transformRect(sf::FloatRect(0.f,0.f,100.f,26.f));
    s = this->getRGTransform().getInverse().transformPoint(s,10.f).x;
//    float offset = kor.getPosition().x;
    float x;
    if (s > width) {
        x = width;
    } else if (s < 0.f) {
        x = 0.f;
    } else {
        x = s;
    }
    currposition = x;
    kor.setPosition(x, height/2);
    updateNumeric();
}

double Knob::getValue() const {
    double value;
    if (exponential) {
       value = 3*pow(10,currposition/10);
    } else {
       value = (max-min)/width * currposition;
    }
    return value;
}

void Knob::updateNumeric() {
    std::ostringstream convert;
    convert << txt << ": " << getValue();
    label.setString(convert.str());
}
void Knob::setValue(double v) {
    if (exponential) {
        currposition = 10*std::log10(v/3);
    } else {
        currposition = (v*width)/(max-min);
    }
    kor.setPosition((float)currposition, height/2);
    updateNumeric();
}
