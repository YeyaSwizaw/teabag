#ifndef TEABAG_GAME_HPP
#define TEABAG_GAME_HPP

#include "defines.hpp"
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

	std::string currentMapName;
	std::vector<std::vector<sf::RectangleShape>> currentMapTiles;

	TileManager tileMan;

	sf::RenderWindow gameWindow;

}; // class Game;

TEABAG_NAMESPACE_END

#endif // TEABAG_GAME_HPP
