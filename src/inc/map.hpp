#ifndef TEABAG_MAP_HPP
#define TEABAG_MAP_HPP

#include "defines.hpp"
#include "optionsparser.hpp"

TEABAG_NS

class Game;

/**
 * Loads and manages the game map.
 * This class is used internally to load, store data about, and render maps.
 */
class GameMap {
private:
	friend class Game;

	GameMap();

	int loadMap(std::string mapname);

}; // class GameMap;

TEABAG_NS_END

#endif // TEABAG_MAP_HPP
