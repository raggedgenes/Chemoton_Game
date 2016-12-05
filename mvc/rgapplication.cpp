#include "rgapplication.h"
#include "../display/curve.h"
#include "../display/plot.h"
#include "../gui/layer.h"
#include "../gui/toggletextbutton.h"
#include <limits>
#include "../gui/knob.h"
using namespace rg;
Application::Application()
{
//   std::cout << "app:init" << std::endl;
    this->isRunning = init();
}

bool Application::init()
{
//    std::cout << "app1" << std::endl;
    guiwidth = 200.f;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(1000, 400, 32), "Chemoton app - Makai & Bekes 2013", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar, settings);
    window.resetGLStates();
    sysfont.loadFromFile("r/font.ttf");
//    window.setFramerateLimit(60);
//    std::cout << "app2" << std::endl;
    return true;
}
bool Application::run()
{
    gui.setLayout('v');
    dashboard.setLayout('v');
    gui.setSize(sf::Vector2f(guiwidth, window.getSize().y));
    dashboard.setTranslate(guiwidth,0.f);

    chemoton = new gt::RungeKuttaEngine();

    float prev = 0.f;
    float out_t = 0.3f;
    int reagent = 7;
    std:string zold = "pVn";
//ez a rész ideiglenes
    rg::Layer menu = rg::Layer();
    menu.setLayout('h');
    menu.gap = 4.f;
    menu.padding = 0.f;
    dashboard.addItem(menu);

    Plot plot;
    chemoton->register_observer(rg::Event("division"), &plot);
    Curve vcurve("monomer");
    Curve scurve ("surface");
    Curve ccurve(zold);
    Curve ocurve("osmosis");
    vcurve.setColor(sf::Color::Yellow);
    scurve.setColor(sf::Color::Red);
    ccurve.setColor(sf::Color::Green);
    ocurve.setColor(sf::Color::Blue);
    plot.addCurve(&vcurve);
    plot.addCurve(&scurve);
    plot.addCurve(&ccurve);
    plot.addCurve(&ocurve);
    plot.stretching = true;

    rg::Knob polymKnob = rg::Knob("Polymer length", true, sysfont);
//    std::cout << "run1" << std::endl;
    polymKnob.setTranslate(5.f, 0.f);
    polymKnob.setValue(25.f);

    rg::Knob resol = rg::Knob("Resolution", false, sysfont);
    resol.min = 0.01;
    resol.max = 1;
    resol.setTranslate(5.f, 0.f);
    resol.setValue(0.06);
    rg::Knob limit1 = rg::Knob("Polim'tion start", false, sysfont);
    limit1.setTranslate(5.f, 0.f);
    limit1.setValue(30.f);
    rg::Knob limit2 = rg::Knob("Polim'tion stop", false, sysfont);
    limit2.setTranslate(5.f, 0.f);
    limit2.setValue(1.f);
    rg::Knob membrane = rg::Knob("Membrane size", false, sysfont);
    membrane.min = 1;
    membrane.max = 1000;
    membrane.setTranslate(5.f, 0.f);
    membrane.setValue(30.f);

    gui.addItem(resol);
    gui.addItem(polymKnob);
    gui.addItem(limit1);
    gui.addItem(limit2);
    gui.addItem(membrane);

    rg::ToggleTextButton playButton("Pause", "Play");
    rg::TextButton restartButton("Restart");
    rg::Label divtime("Repl. time:");
    restartButton.id = 10;
    restartButton.register_observer(rg::Event("clicked"),this);
    menu.addItem(playButton);
    menu.addItem(restartButton);
    menu.addItem(divtime);
    menu.autoSize();
    dashboard.addItem(plot);

    playButton.onClick();

    onResize();
    clock.restart();
//    std::cout << "run2" << std::endl;
    // idáig
    while(window.isOpen())
    {
        //checking for dashboard interaction
        sf::Vector2i mouse= sf::Mouse::getPosition(window);
        //gui egér ellenõrzés
        sf::Vector2f mot= gui.getRGTransform().getInverse().transformPoint(sf::Vector2f((float)mouse.x, (float)mouse.y));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (polymKnob.isIn(mot)) {
                polymKnob.slide(mot.x);
            } else if (resol.isIn(mot)){
                resol.slide(mot.x);
                out_t = resol.getValue();
            } else if (limit1.isIn(mot)) {
                limit1.slide(mot.x);
            } else if (limit2.isIn(mot)) {
                limit2.slide(mot.x);
            } else if (membrane.isIn(mot)) {
                membrane.slide(mot.x);
            }
        }
         chemoton->setPolymerLength(polymKnob.getValue());
         chemoton->setMembraneSize(membrane.getValue());
         *(chemoton->polymLimitUp) =  limit1.getValue();
         *(chemoton->polymLimitDown) = limit2.getValue();
        divtime.text.setString(chemoton->replicationtime);
        //dashboard egér ellenõrzés
        mot= dashboard.getRGTransform().getInverse().transformPoint(sf::Vector2f((float)mouse.x, (float)mouse.y));
        playButton.isIn(mot);
        restartButton.isIn(mot);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

            if (playButton.isIn(mot)) {
                if (clock.getElapsedTime().asMilliseconds() > 300 ) {
                    playButton.onClick();
                     clock.restart();
                }
            } else if (restartButton.isIn(mot)) {
                if (clock.getElapsedTime().asMilliseconds() > 300 ) {
                    restartButton.onClick();
                    prev = 0.f;
                     clock.restart();
                }
            } else if (plot.isIn(mot)){
                plot.makeVertcialLine(mot.x);
            }
        }
        if (!playButton.isOn()) {
//            sf::Vector2f ertek = chemoton->engine.nextStep(reagent);
            double time = chemoton->step();
            if((time - prev) >= out_t)
            {
                prev = time;
                plot.addValueTo(0,sf::Vector2f(prev, chemoton->getMonomerConc()));
                plot.addValueTo(2,sf::Vector2f(prev, chemoton->getValueByName(zold)));
                plot.addValueTo(1,sf::Vector2f(prev, chemoton->getSurface()));
                plot.addValueTo(3, sf::Vector2f(prev,chemoton->getOsmosis()));
                window.clear(sf::Color::Black);
                window.draw(gui);
                window.draw(dashboard);
                window.display();
            }
        } else {
            window.clear(sf::Color::Black);
            window.draw(gui);
            window.draw(dashboard);
            window.display();
        }
        limit2.setValue(*(chemoton->polymLimitDown));
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {
                window.close();
                break;
            } else if(event.type == sf::Event::Resized) {
                onResize();
            } else if(event.type == sf::Event::MouseButtonReleased) {
//                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
//                    text.onClick();
//                }
            } else if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                case sf::Keyboard::Num0 :
                    reagent = 11;
                    break;
                case sf::Keyboard::Num8 :
                    reagent = 8;
                    break;
                case sf::Keyboard::Num9 :
                    reagent = 9;
                    break;
                default:
                    reagent = 7;
                }
            }
        }
    }
    return true;
}
void Application::onResize()
{
    sf::Vector2f size = static_cast<sf::Vector2f>(window.getSize());

    // Minimum size
    if(size.x < 400)
        size.x = 400;
    if(size.y < 400)
        size.y = 400;

    // Apply possible size changes
    window.setSize(static_cast<sf::Vector2u>(size));
//    main.setSize(size);
    gui.setSize(sf::Vector2f(guiwidth, size.y));
    dashboard.setSize(sf::Vector2f(size.x - guiwidth,size.y));
    sf::View v;
    v.reset(sf::FloatRect(0.f,0.f,size.x, size.y));
    window.setView(v);
}
void Application::notify(Event e, Subject *caller){
    switch (caller->id) {
    case 10: // restart button
        chemoton->restart();
        break;
    }
    if (e.type() == "division") {

    }
}

