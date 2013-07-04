#ifndef TEABAG_MAP_HPP
#define TEABAG_MAP_HPP

#include "defines.hpp"
#include "tileman.hpp"
#include "sprman.hpp"
#include "entman.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

TEABAG_NAMESPACE_BEGIN

class Game;
class EventManager;

class GameMap {
public:
	GameMap(TileManager *tileMan, SpriteManager *sprMan, EntityManager *entMan);

	int loadMap(std::string name);
	int loadMap();

private:
	friend class Game;
	friend class EventManager;

	TileManager *tileMan;
	SpriteManager *sprMan;
	EntityManager *entMan;

	unsigned int tileSize;

	std::string mapName;
	std::vector<std::vector<sf::RectangleShape>> mapTiles;
	std::vector<std::vector<std::string>> mapTileNames;

}; // class GameMap;

TEABAG_NAMESPACE_END

#endif // TEABAG_MAP_HPP
