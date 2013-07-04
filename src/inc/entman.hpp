#ifndef TEABAG_ENTMAN_HPP
#define TEABAG_ENTMAN_HPP

#include "defines.hpp"
#include "entity.hpp"
#include "sprman.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>

TEABAG_NAMESPACE_BEGIN

class Game;
class EventManager;

class EntityManager {
public:
	EntityManager();

	int loadEntity(int x, int y, std::string name);
	int setAllSprites(SpriteManager *sprMan);

	Entity* getEntity(std::string name);

private:
	friend class Game;
	friend class EventManager;

	std::unordered_map<std::string, Entity> entities;

}; // class EntityManager;

TEABAG_NAMESPACE_END

#endif // TEABAG_ENTMAN_HPP
