#ifndef RGAPPLICATION_H
#define RGAPPLICATION_H

#include <SFML/Graphics.hpp>
#include "../gui/layer.h"
#include "../Observer/eventdispatcher.h"
#include "../chemoton/rungekuttaengine.h"
namespace rg {

class Application : public rg::Observer
{
public:
        /// @brief Constructor.
        ///
        Application();

        /// @brief Initialization with possible error returner.
        /// @return True in case everything got initialized correctly, false otherwise.
        bool init();

        /// @brief Starts the application, that includes create a window and managing the GUI, etc.
        /// @return True in case everything run correctly, false otherwise.
        bool run();

        /// @brief Callback function if button 'put' is pressed.
        ///
//        void onClickPut();

        /// @brief Callback function if button 'remove' is pressed.
        ///
//        void onClickRemove();

        /// @brief Callback function if button 'exit' is pressed.
        ///
        void onClickExit();

        /// @brief Callback function if the window gets resized. Can also be used to update the views.
        ///
        void onResize();
        void notify(rg::Event e, Subject* caller);

private:
        // Window
        sf::RenderWindow window;
        sf::View guiview;
        sf::View workview;
        float guiwidth;
        sf::Clock clock;
        Layer gui;
        Layer dashboard;
        bool isRunning;
        sf::Font sysfont;
        gt::RungeKuttaEngine *chemoton;
//        Layer main;
};

}
#endif // RGAPPLICATION_H
