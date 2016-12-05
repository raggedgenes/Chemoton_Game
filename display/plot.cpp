#include "plot.h"

Plot::Plot()
{
    curves = std::vector<Curve*>();
    legend = std::vector<rg::Label*>();
    lines = sf::VertexArray(sf::Lines, 2);
    size = sf::Vector2f(100.f, 100.f);
}
bool Plot::isIn(sf::Vector2f mouse)
{
    sf::FloatRect bound = this->getRGTransform().transformRect(sf::FloatRect(0.f,0.f,getSize().x,getSize().y));
    if (bound.contains(sf::Vector2f((float)mouse.x, (float)mouse.y))) {
        return true;
    } else {
        return false;
    }
}
int Plot::addCurve(Curve *curve) {
    curve->setSize(this->size);
    curves.push_back(curve);
    rg::Label* lbl = new rg::Label(curve->label);
    lbl->setColor(curve->color);
    lbl->setTranslate(0.f, 20.f*(legend.size()));
    legend.push_back(lbl);
    return 0;
}

void Plot::removeCurveAt(int index) {
//    curves.erase();
}
void Plot::setSize(sf::Vector2f size) {

    for (unsigned int i = 0; i < curves.size(); i++) {
        curves[i]->setSize(size);
    }
    this->size = size;
}
sf::Vector2f Plot::getSize() const {
    return this->size;
}
void Plot::build() {
//    float min = curves[0]->data.front().x;
//    std::vector<float> templines = std::vector<float>();
//    for (int i = 0; i < vlines.size(); i++) {
//        vlines[i]-= 1.f;
//        if (vlines[i] > 0) {
//            templines.push_back(vlines[i]);
//        }
//    }
//    vlines = templines;
//    lines = sf::VertexArray(sf::Lines, vlines.size()*2);
//    for (int i = 0; i < vlines.size()*2; i += 2) {
//        lines[i].position = sf::Vector2f(vlines[i], 0);
//        lines[i+1].position = sf::Vector2f(vlines[i], getSize().y);
//    }
}
void Plot::makeVertcialLine(float ide) {
    lines[0].position = sf::Vector2f(ide, 0);
    lines[1].position = sf::Vector2f(ide, getSize().y);
}

void Plot::addValueTo(int index, sf::Vector2f ertek) {
    curves.at(index)->addData(ertek);
}
void Plot::addValueTo(Curve * curve, sf::Vector2f ertek) {
    curve->addData(ertek);
}

void Plot::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getRGTransform();
    sf::RectangleShape keret;
    keret.setSize(this->size);
    keret.setFillColor(sf::Color(42,56,54));
    target.draw(keret,states);
    for (unsigned int i = 0; i < curves.size(); i++) {
        Curve* curve = curves[i];
        if (curve->visible) {
            curve->build();
            target.draw(curve->getDrawable(), curve->getVertexSize(), curve->getType(), states);
        }
    }
    if (this->curves.size() > 0) {
            target.draw(lines, states);
    }
    sf::RenderStates arch = states;
    for (unsigned int l = 0; l < legend.size(); l++) {
        if (curves.at(l)->visible) {
            rg::Label* lbl = legend[l];
            states.transform *= lbl->getRGTransform();
            target.draw(lbl->text, states);
            states = arch;
        }
    }
    //make frame

}
void Plot::notify(rg::Event e, rg::Subject *self) {
//    if (e.type() == "division") {
//        this->makeVertcialLine();
//    }
}
