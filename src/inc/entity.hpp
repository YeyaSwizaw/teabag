#ifndef TEABAG_ENTITY_HPP
#define TEABAG_ENTITY_HPP

#include <functional>

#include "defines.hpp"
#include "eventmanager.hpp"
#include "entitymanager.hpp"

#include <SFML/Graphics.hpp>

TEABAG_NS

class Game;

class Entity {
public:
	Entity();

	void move(int xd, int yd);
	void onCollision(CollisionCallback callback);

	sf::FloatRect getBounds();
	int getX();
	int getY();

private:
	friend class Game;

	bool valid;

	Entity(std::string name, internal::EntityManager* entMan, internal::EventManager* evtMgr);

	std::function<void(int, int)> funcMove;
	std::function<void(CollisionCallback)> funcCollision; 
	std::function<sf::FloatRect()> funcGetBounds;

}; // class Entity;

TEABAG_NS_END

#endif // TEABAG_ENTITY_HPP
