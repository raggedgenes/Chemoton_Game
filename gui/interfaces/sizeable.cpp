#include "sizeable.h"

Sizeable::Sizeable() : stretching(false)
{
}
void Sizeable::setTranslate(float x, float y) {
   rg_transform = sf::Transform();
   rg_transform.translate(x,y);
}
sf::Transform Sizeable::getRGTransform() const {
   return rg_transform;
}
