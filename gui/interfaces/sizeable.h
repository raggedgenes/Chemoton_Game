#ifndef SIZEABLE_H
#define SIZEABLE_H
#include <SFML/Graphics.hpp>

class Sizeable : public sf::Drawable
{
public:
    Sizeable();
    virtual void setSize(sf::Vector2f size) = 0;
    virtual sf::Vector2f getSize() const = 0;
    virtual bool isIn(sf::Vector2f mouse) = 0;
    void setWidth(float w);
    void setHeight(float h);
    void setTranslate(float x, float y);
    sf::Transform getRGTransform() const;
    bool stretching;
    sf::Transform rg_transform;
protected:
    sf::Vector2f size;

private:

};
inline void Sizeable::setWidth(float w) {
    this->size.x = w;
}
inline void Sizeable::setHeight(float h) {
    this->size.y = h;
}
#endif // SIZEABLE_H
