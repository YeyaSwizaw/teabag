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
	void onCollision(std::function<void(sf::FloatRect, sf::FloatRect, sf::FloatRect)> callback);

private:
	friend class Game;

	bool valid;

	Entity(std::string name, internal::EntityManager* entMan, internal::EventManager* evtMgr);

	std::string name;

	std::function<void(int, int)> funcMove;
	std::function<void(std::string, std::function<void(sf::FloatRect, sf::FloatRect, sf::FloatRect)>)> funcCollision; 

}; // class Entity;

TEABAG_NS_END

#endif // TEABAG_ENTITY_HPP
