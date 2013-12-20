#ifndef TEABAG_ENTITY_HPP
#define TEABAG_ENTITY_HPP

#include "defines.hpp"
#include "entitymanager.hpp"

#include <SFML/Graphics.hpp>

TEABAG_NS

class Game;

class Entity {
public:
	Entity();

	void move(int xd, int yd);

private:
	friend class Game;

	bool valid;

	Entity(sf::Sprite* e);

	sf::Sprite* entity;

}; // class Entity;

TEABAG_NS_END

#endif // TEABAG_ENTITY_HPP
