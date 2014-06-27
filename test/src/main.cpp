#include "teabag/game.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
    teabag::Game g;
    g.init();

    bool up = false, down = false, left = false, right = false;

    g.signals().close().connect([&g](){ g.exit(); });
    g.signals().resize().connect([&g](int w, int h){ g.resizeView(w, h); });
    g.signals().mousePress().connect([](sf::Mouse::Button b, int x, int y){ std::cout << "(" << x << ", " << y << "): " << b << std::endl; });

    g.signals().keyPress().connect([&up, &down, &left, &right](sf::Keyboard::Key k, bool a, bool b, bool c, bool d) {
        switch(k) {
            case sf::Keyboard::Up:
                up = true;
                break;

            case sf::Keyboard::Down:
                down = true;
                break;

            case sf::Keyboard::Left:
                left = true;
                break;

            case sf::Keyboard::Right:
                right = true;
                break;

            default:
                break;
        } 
    });

    g.signals().keyRelease().connect([&up, &down, &left, &right](sf::Keyboard::Key k, bool a, bool b, bool c, bool d) {
        switch(k) {
            case sf::Keyboard::Up:
                up = false;
                break;

            case sf::Keyboard::Down:
                down = false;
                break;

            case sf::Keyboard::Left:
                left = false;
                break;

            case sf::Keyboard::Right:
                right = false;
                break;

            default:
                break;
        } 
    });

    g.signals().tick().connect([&g, &up, &down, &left, &right]() {
        g.world().entity("player").move(
            left ? -1 : (right ? 1 : 0),
            up ? -1 : (down ? 1 : 0)
        );
    });

    g.world().loadLevel("forest1");

    g.run();
} 
