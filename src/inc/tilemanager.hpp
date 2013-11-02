#ifndef TEABAG_TILEMANAGER_HPP
#define TEABAG_TILEMANAGER_HPP

#include "defines.hpp"

#include <unordered_map>
#include <functional>
#include <sstream>
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

TEABAG_NS

class GameMap;

/**
 * This struct stores the information for a tile.
 * The information is loaded from the tile's .tea file, and consists of
 * the colour representing this tile on the map img; the name of the tile;
 * whether the tile is blocking or not; and the tile's texture.
 */
struct TileInfo {
	std::string name;
	sf::Color colour;
	bool blocking;
	sf::Texture texture;

}; // struct TileInfo;

class TileManager {
private:
	friend class GameMap;

	TileManager();
	~TileManager();

	int addTile(std::string name, int r, int g, int b, bool blocking);

	TileInfo* getTile(sf::Color c);
	TileInfo* getTile(std::string name);

	void clear();

	std::unordered_map<sf::Color, TileInfo*, std::function<size_t(sf::Color)>> colourMap;
	std::unordered_map<std::string, TileInfo*> nameMap;

}; // class TileManager;

TEABAG_NS_END

#endif // TEABAG_TILEMANAGER_HPP
