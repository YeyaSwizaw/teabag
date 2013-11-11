#ifndef TEABAG_ENTITYMANAGER_HPP
#define TEABAG_ENTITYMANAGER_HPP

#include "defines.hpp"
#include "optionsparser.hpp"

#include <unordered_map>

#include <SFML/Graphics.hpp>

TEABAG_NS

typedef sf::Sprite Entity;

class Game;
class GameMap;

class EntityManager {
private:
	friend class Game;
	friend class GameMap;

	EntityManager();
	~EntityManager();

	int addEntity(std::string name, int x, int y);

	Entity* getEntity(std::string name);

	std::unordered_map<std::string, sf::Texture> texMap;
	std::unordered_map<std::string, Entity> entityMap;

}; // class EntityManager;


TEABAG_NS_END

#endif // TEABAG_ENTITYMANAGER_HPP
