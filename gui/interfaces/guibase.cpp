#include "guibase.h"
using namespace  rg;
Guibase::Guibase()
{
}
//void Guibase::draw(sf::RenderTarget &target, sf::RenderStates states) const{

//}
void Guibase::setSize(sf::Vector2f size){
    this->size = size;
}
sf::Vector2f Guibase::getSize() const {
    return this->size;
}

