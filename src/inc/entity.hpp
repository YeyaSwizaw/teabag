#ifndef TEABAG_ENTITY_HPP
#define TEABAG_ENTITY_HPP

#include "defines.hpp"

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

TEABAG_NAMESPACE_BEGIN

class Game;
class Map;
class EntityManager;

class Entity {
public:
	Entity(sf::Vector2f pos, std::string sprName, sf::Vector2i sprPos);

private:
	friend class Game;
	friend class Map;
	friend class EntityManager;

	std::string sprName;
	sf::Vector2i sprPos;
	sf::Sprite sprite;

}; // class Entity;

TEABAG_NAMESPACE_END

#endif // TEABAG_ENTITY_HPP
