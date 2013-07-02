#ifndef TEABAGTEST_HPP
#define TEABAGTEST_HPP

#include "../../../src/inc/game.hpp"

#include <functional>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Test {
public:
	Test();

	int run();

	void moveEntity(sf::Event e);

private:
	teabag::Game g;

}; // class Test;

#endif // TEABAGTEST_HPP
