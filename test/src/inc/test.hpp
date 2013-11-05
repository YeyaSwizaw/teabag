#ifndef TEABAGTEST_HPP
#define TEABAGTEST_HPP

#include "../../../src/inc/game.hpp"

#include <SFML/System.hpp>

class Test {
public:
	Test();

	int run();

	void keyPressed(sf::Event e);

private:
	teabag::Game g;

}; // class Test;

#endif // TEABAGTEST_HPP
