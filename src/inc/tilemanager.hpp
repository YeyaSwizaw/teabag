#ifndef TEABAG_TILEMANAGER_HPP
#define TEABAG_TILEMANAGER_HPP

#include "defines.hpp"
#include "error.hpp"
#include "tile.hpp"

#include <string>
#include <unordered_map>
#include <functional>
#include <utility>
#include <algorithm>

#include <SFML/Graphics.hpp>

TEABAG_NS

class World;
class Map;

TEABAG_INTERNAL

struct TileInfo {
    std::string name;
    int r, g, b;
    bool blocking;
}; 

class TileManager {
private:
    friend class teabag::World;
    friend class teabag::Map;

    TileManager();

    void queueTile(std::string name, int r, int g, int b, bool blocking);
    void loadQueue();
    void loadTile(TileInfo& tile);

    const Tile& tileFromName(std::string name);
    const Tile& tileFromColour(sf::Color colour);

    unsigned int tileWidth();
    unsigned int tileHeight();

    std::vector<TileInfo> tileQueue;

    std::unordered_map<std::string, Tile> tiles;
    std::unordered_map<sf::Color, std::string, std::function<size_t(sf::Color)>> colours;

    unsigned int tileW;
    unsigned int tileH;
};

TEABAG_INTERNAL_END

TEABAG_NS_END

#endif
