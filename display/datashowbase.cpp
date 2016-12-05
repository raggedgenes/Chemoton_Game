#include "datashowbase.h"
#include <limits>
#include <math.h>

DataShowBase::DataShowBase(std::string name) : label(name)
{
    setSize(sf::Vector2f(100.f, 100.f));
    rangex.x = std::numeric_limits<float>::max();
    rangey.x = std::numeric_limits<float>::min();
    rangey.x = std::numeric_limits<float>::max();
    rangey.y = std::numeric_limits<float>::min();
}
DataShowBase::DataShowBase(std::string name, sf::Vector2f size_)
{
    label = name;
    this->size = size_;
    rangex.x = std::numeric_limits<float>::max();
    rangey.x = std::numeric_limits<float>::min();
    rangey.x = std::numeric_limits<float>::max();
    rangey.y = std::numeric_limits<float>::min();
//    init();
}
void DataShowBase::makeRanges() {

//    rangex.x = std::numeric_limits<float>::max();
//    rangey.x = std::numeric_limits<float>::min();
//    rangey.x = std::numeric_limits<float>::max();
//    rangey.y = std::numeric_limits<float>::min();

    rangex.x = 0;
    rangex.y = size.x;

    if(data.size() > 1)
    {
        if(rangey.x == std::numeric_limits<float>::max())
        {
            rangey.x = data.front().y;
//            rangey->x = 0;
        }
        if(rangey.y == std::numeric_limits<float>::min())
        {
            rangey.y = data.front().y;
        }
        // calculate the min and max for the y-axis value
        for(std::list<sf::Vector2f>::iterator it=data.begin();it!=data.end();++it)
        {
             sf::Vector2f k = (sf::Vector2f) *it;
//             min
            if(k.y < rangey.x)
            {
                rangey.x = k.y;
            }
//             max
            if(k.y > float(rangey.y))
            {
                rangey.y = k.y;
            }
        }
    }

}

void DataShowBase::setSize(const sf::Vector2f s){
    this->size = s;
}
sf::Vector2f DataShowBase::getSize() const {
    return size;
}
