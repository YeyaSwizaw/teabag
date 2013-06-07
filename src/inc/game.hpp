#ifndef TEABAG_GAME_HPP
#define TEABAG_GAME_HPP

#include "defines.hpp"
#include "map.hpp"
#include "tileman.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <list>

#include <SFML/Graphics.hpp>

TEABAG_NAMESPACE_BEGIN

class Game {
public:
	Game();

	int init(bool loadMapNow = true);

	int loadMap();
	int loadMap(std::string mapName);

	int run();

private:
	std::string gameName;

	TileManager tileMan;
	GameMap gameMap;

	sf::RenderWindow gameWindow;

}; // class Game;

TEABAG_NAMESPACE_END

#endif // TEABAG_GAME_HPP
