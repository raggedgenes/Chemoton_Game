#include "curve.h"
#include <cmath>

Curve::Curve(std::string name) : DataShowBase(name)
{
    init();
}

Curve::Curve(std::string name, sf::Vector2f size) : DataShowBase(name, size) {
    init();
}

void Curve::init() {
    setColor(sf::Color(19, 13, 200));
    thickness = 1;
    xshift = 0.f;
    visible = true;
}

void Curve::addData(sf::Vector2f _data)
{
    this->data.push_back(_data);
    while (this->data.size() > size.x) {
        this->data.pop_front();
    }
//  if(this->data.size() > size.x)
//  {
////      sf::Vector2f last = data.back();
////      data.clear();
////      data.push_back(last);
////      this->xshift = data.front().x;
////       this->data.push_back(_data);
//  }
}
//
void Curve::build() {

    this->makeRanges();
    float distance = fabs(rangey.y-rangey.x);
    this->line.clear();
    sf::Vector2f prev = data.front();
    prev.x = 0;
    int counter = 0;

    for (std::list<sf::Vector2f>::iterator it = data.begin()++; it != data.end(); ++it) {
        if (it == data.begin()) continue;
        sf::Vector2f v = (sf::Vector2f) *it;
        float realy = (v.y - rangey.x) / distance;
        v.x = counter;
//        v.y = size.y - v.y*10.f;
        v.y = size.y - size.y * realy;
        line.push_back(sf::Vertex(makeItThick(v, prev, 1), color));
        line.push_back(sf::Vertex(makeItThick(v, prev, -1), color));
        line.push_back(sf::Vertex(makeItThick(prev,v, 1), color));
        line.push_back(sf::Vertex(makeItThick(prev,v, -1), color));
        prev = v;
        counter++;
    }
    line.erase(line.begin(), line.begin()+4);
}

sf::Vector2f Curve::makeItThick(sf::Vector2f actual, sf::Vector2f prev, int factor) {
    sf::Vector2f diff = actual - prev;
    float d = std::sqrt(diff.x*diff.x + diff.y*diff.y);
    float x = factor*(thickness*diff.y)/d;
    float y = -1*factor*(thickness*diff.x)/d;
    return sf::Vector2f(prev.x + x, prev.y + y);
}

sf::Vertex* Curve::getDrawable() {
    return &line[0];
}
int Curve::getVertexSize() {
    return line.size();
}
sf::PrimitiveType Curve::getType() {
    return sf::Quads;
}

