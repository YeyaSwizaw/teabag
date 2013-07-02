#ifndef TEABAG_GAME_HPP
#define TEABAG_GAME_HPP

#include "defines.hpp"
#include "map.hpp"
#include "tileman.hpp"
#include "sprman.hpp"
#include "entman.hpp"
#include "eventman.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <list>
#include <functional>

#include <SFML/Graphics.hpp>

TEABAG_NAMESPACE_BEGIN

class Game {
public:
	Game();

	int init(bool loadMapNow = true);

	int loadMap();
	int loadMap(std::string mapName);

	int addEventCallback(sf::Event::EventType sfEventType, std::function<void(sf::Event)> func);

	Entity* getEntity(std::string name);

	int run();

	int quit();

private:
	std::string gameName;

	TileManager tileMan;
	SpriteManager sprMan;
	EntityManager entMan;
	GameMap gameMap;

	EventManager eventMan;

	sf::RenderWindow gameWindow;

}; // class Game;

TEABAG_NAMESPACE_END

#endif // TEABAG_GAME_HPP
