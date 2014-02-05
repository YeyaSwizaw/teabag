#ifndef RPG_RPG_HPP
#define RPG_RPG_HPP

#include "player.hpp"

#include <teabag/game.hpp>

#include <SFML/Window.hpp>

class RPG {
public:
	RPG();

	int run();

	void mouseRelease(sf::Event e);
    void onResize(sf::Event e);

private:
	teabag::Game g;
	Player player;

}; // class RPG;

#endif // RPG_RPG_HPP
