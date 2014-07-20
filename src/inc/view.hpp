#ifndef TEABAG_VIEW_HPP
#define TEABAG_VIEW_HPP

#include "defines.hpp"
#include "ui.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

TEABAG_NS

class Game;

class View {
public:
    /**
     * Resizes the view.
     */
    void resize(int w, int h);

    /**
     * Scrolls the view.
     */
    void scroll(int x, int y);

    /**
     * Centers the view on a location.
     */
    void centerOn(int x, int y);

private:
    friend class Game;

    sf::RenderWindow window;
    UI ui;
};

TEABAG_NS_END

#endif
