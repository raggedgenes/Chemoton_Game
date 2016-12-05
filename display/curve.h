#ifndef CURVE_H
#define CURVE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "datashowbase.h"

class Curve : public DataShowBase
{
public:
    Curve(std::string name);
    Curve(std::string name, sf::Vector2f size);
    void setThickness(float th);
    sf::Vertex* getDrawable();
    int getVertexSize();
    sf::PrimitiveType getType();
    void addData(sf::Vector2f _data);
    void build();
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {}
    float thickness;
    std::vector<sf::Vertex> line;
    sf::Vector2f makeItThick(sf::Vector2f actual, sf::Vector2f prev, int factor);
    void init();
};

inline void Curve::setThickness(float th){
    this->thickness = th;
}

#endif // CURVE_H
