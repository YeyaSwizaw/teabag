#ifndef TEABAG_MAP_HPP
#define TEABAG_MAP_HPP

#include "defines.hpp"
#include "optionsparser.hpp"
#include "entitymanager.hpp"
#include "tilemanager.hpp"

#include <vector>
#include <string>

TEABAG_NS

class Game;

TEABAG_INTERNAL

/**
 * Loads and manages the game map.
 * This class is used internally to load, store data about, and render maps.
 */
class GameMap {
private:
	friend class teabag::Game;

	GameMap();

	int loadMap(std::string mapname);

	int loadText(std::string mapname);
	int loadImg(std::string mapname);
	int renderTex();

	TileManager tileManager;
	EntityManager entityManager;

	std::vector<std::vector<std::string>> tileNames;
	std::vector<std::string> entityNames;

	sf::RenderTexture mapTex;

}; // class GameMap;

TEABAG_INTERNAL_END

TEABAG_NS_END

#endif // TEABAG_MAP_HPP
