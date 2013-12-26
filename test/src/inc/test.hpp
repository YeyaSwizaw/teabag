#ifndef TEABAGTEST_HPP
#define TEABAGTEST_HPP

#include "../../../src/inc/game.hpp"

#include <SFML/System.hpp>

class Test {
public:
	Test();

	int run();

	void playerCollision(sf::FloatRect e1, sf::FloatRect e2, teabag::Collision coll);

private:
	teabag::Game g;
	teabag::Entity player;

}; // class Test;

#endif // TEABAGTEST_HPP
