#ifndef PLOT_H
#define PLOT_H

#include <SFML/Graphics.hpp>
#include "curve.h"
#include "../gui/interfaces/sizeable.h"
#include "../gui/label.h"
#include "../observer/eventdispatcher.h"

class Plot : public Sizeable, public sf::Transformable, public rg::Observer
{
public:
    Plot();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void build();
    int addCurve(Curve *curve);
    void removeCurveAt(int index);
    void setSize(sf::Vector2f size);
    sf::Vector2f getSize() const;
    bool isIn(sf::Vector2f mouse);
    void addValueTo(Curve*, sf::Vector2f ertek);
    void addValueTo(int index, sf::Vector2f ertek);
    void makeVertcialLine(float ide);
    void notify(rg::Event e, rg::Subject *self);
private:
    std::vector<Curve*> curves;
    std::vector<rg::Label*> legend;
    std::vector<float> vlines;
    sf::VertexArray lines;
};

#endif // PLOT_H
