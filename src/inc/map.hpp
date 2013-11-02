#ifndef TEABAG_MAP_HPP
#define TEABAG_MAP_HPP

#include "defines.hpp"
#include "optionsparser.hpp"
#include "tilemanager.hpp"

#include <vector>
#include <string>

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

	int loadText(std::string mapname);
	int loadImg(std::string mapname);

	TileManager tileManager;

	std::vector<std::vector<std::string>> tileNames;

}; // class GameMap;

TEABAG_NS_END

#endif // TEABAG_MAP_HPP
