#include "layer.h"
#include "interfaces/sizeable.h"
using namespace rg;
Layer::Layer()
{
    elements = std::vector<Sizeable*>();
    padding = 4.f;
    gap = 2.f;
}
Layer::~Layer(){
    for(std::vector<Sizeable*>::iterator it = elements.begin(); it != elements.end(); ++it) {
        delete *(it);
    }
}

void Layer::addItem(Sizeable &mit) {
    elements.push_back(&mit);
//    positionThis(elements.size()-1);
}

void Layer::positionThis(int index) {
//    if (index > 0){
//        sf::Vector2f pos = ((sf::Transformable*)elements.at(index-1))->getPosition();
//        sf::Vector2f siz = ((Sizeable*)elements.at(index-1))->getSize();
//        if (layout == 'h' ) pos.x += siz.x;
//        if (layout == 'v') pos.y += siz.y;
//        ((sf::Transformable*)elements.at(index))->setPosition(pos);
//    } else {
//        ((sf::Transformable*)elements.at(index))->setPosition(sf::Vector2f(padding, padding));
//    }

}

void Layer::setLayout(char lo){
   this->layout = lo;
}
void Layer::handleMouseEvent(sf::Mouse mouse) {

}

void Layer::resize() {
    std::vector<Sizeable*> stretch = std::vector<Sizeable*>();
    float w = size.x-2.f*padding;
    float h = size.y-2.f*padding;
    if (elements.size() > 1)
    {
        for(unsigned int d = 0; d < elements.size(); d++) {
            sf::Vector2f tmp = ((Sizeable*) elements.at(d))->getSize();
            if (((Sizeable*) elements.at(d))->stretching) {
                stretch.push_back(elements.at(d));
            } else {
                h -= tmp.y;
                w -= tmp.x;
            }
            if (d > 0) {
                h -= gap;
                w -= gap;
            }
            if (layout == 'v') {
                tmp.x = this->getSize().x - padding*2;
                //tmp.y -= padding*2;
                ((Sizeable*) elements.at(d))->setSize(tmp);
            } else if (layout == 'h') {
                tmp.y = this->getSize().y - padding*2;
                //tmp.x -= padding*2;
                ((Sizeable*) elements.at(d))->setSize(tmp);
            } else {
                ((Sizeable*) elements.at(d))->setSize(size);
            }
        }
        if (stretch.size() > 0){
            w /= stretch.size();
            h /= stretch.size();
            for(unsigned int d = 0; d < stretch.size(); d++) {
                sf::Vector2f tmp = ((Sizeable*) stretch.at(d))->getSize();
                switch (layout) {
                case 'v':
                    ((Sizeable*) stretch.at(d))->setSize(sf::Vector2f(tmp.x, h));
                    break;
                case 'h':
                    ((Sizeable*) stretch.at(d))->setSize(sf::Vector2f(w, tmp.y));
                    break;
                    //            default:
                }
            }
        }
        //positionning
//        sf::Vector2f prevpos = ((sf::Transformable*)elements.at(d-1))->getPosition();
        sf::Vector2f prevpos = sf::Vector2f(0.f,0.f);
        for(unsigned int d = 0; d < elements.size(); d++) {
            if (d > 0){
                sf::Vector2f prevsize = ((Sizeable*) elements.at(d-1))->getSize();
                switch (layout) {
                case 'v':
                    ((Sizeable*)elements.at(d))->setTranslate(padding, padding+prevsize.y+prevpos.y+gap);
                    prevpos = sf::Vector2f(padding, padding+prevsize.y+prevpos.y+gap);
                    break;
                case 'h':
                    ((Sizeable*)elements.at(d))->setTranslate(padding+prevsize.x+prevpos.x+gap, padding);
                    prevpos = sf::Vector2f(padding+prevsize.x+prevpos.x+gap, padding);
                    break;
                }
            } else {
                ((Sizeable*)elements.at(d))->setTranslate(padding, padding);
            }
        }

    } else {

    }
}
void Layer::autoSize() {
    float w = padding*2.f;
    float h = padding*2.f;
    for (unsigned int d = 0; d < elements.size(); d++) {
        sf::Vector2f tmp = ((Sizeable*) elements.at(d))->getSize();
        switch (layout) {
        case 'h':
            w += tmp.x;
            if (h < tmp.y) h = tmp.y;
            break;
        case 'v':
            h += tmp.y;
            if (w < tmp.x) w = tmp.x;
            break;

        }
    }
    this->setWidth(w);;
    this->setHeight(h);
}

void Layer::setSize(sf::Vector2f size) {
    this->size = size;
    resize();
}
sf::Vector2f Layer::getSize() const {
    return this->size;
}
void Layer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getRGTransform();
    for(unsigned int d = 0; d < elements.size(); d++) {
        target.draw(*(sf::Drawable*)elements.at(d), states);
    }
}
