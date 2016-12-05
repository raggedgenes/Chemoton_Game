#ifndef DATASHOWBASE_H
#define DATASHOWBASE_H
#include <SFML/Graphics.hpp>
#include "../gui/interfaces/sizeable.h"
#include <vector>
#include <list>

class DataShowBase : public Sizeable
{
public:
    DataShowBase(std::string name);
    DataShowBase(std::string name, sf::Vector2f size_);
    void setLabel(const std::string &label);
    void setColor(const sf::Color &color);
    void setSize(const sf::Vector2f s);
    bool isIn(sf::Vector2f mouse) {return NULL;}
    sf::Vector2f getSize() const;
    bool visible;
    sf::Vector2f rangex;
    sf::Vector2f rangey;
    std::string label;
    sf::Color color;
    virtual void addData(sf::Vector2f _data) = 0;
    virtual void build() = 0;
    std::list<sf::Vector2f> data;
private:

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {}
    virtual void init() = 0;
    void makeRanges();
    float xshift;
    sf::Vector2f size;
    //std::vector<sf::Vertex> line;
};


inline void DataShowBase::setLabel(const std::string &label)
{
  this->label = label;
}
inline void DataShowBase::setColor(const sf::Color &color)
{
  this->color = color;
}
#endif // DATASHOWBASE_H
