#include "inc/tilemanager.hpp"

TEABAG_NS

TEABAG_INTERNAL

TileManager::TileManager() 
    : colours(10, [](sf::Color c) { return std::hash<int>()(c.r + 255 * (c.g + 255 * (c.b))); }),
      tileW(0), tileH(0) {}

void TileManager::queueTile(std::string name, int r, int g, int b, bool blocking) {
    tileQueue.push_back({name, r, g, b, blocking});
} 

void TileManager::loadQueue() {
    for(TileInfo& tile : tileQueue) {
        loadTile(tile);
    } 

    tileQueue.clear();
} 

void TileManager::loadTile(TileInfo& tile) {
    std::string texfile = TEABAG_TILE_IMG(tile.name);

    sf::Texture tex;
    if(!tex.loadFromFile(texfile)) {
        throw FileOpenError(texfile);
    } 

    tiles[tile.name] = {tile.name, sf::Color(tile.r, tile.g, tile.b), tile.blocking, tex};
    colours[tiles[tile.name].colour] = tile.name;

    tileW = std::max(tileW, tex.getSize().x);
    tileH = std::max(tileH, tex.getSize().y);
} 

const Tile& TileManager::tileFromName(std::string name) {
    return tiles[name];
} 

const Tile& TileManager::tileFromColour(sf::Color colour) {
    return tiles[colours[colour]];
} 

unsigned int TileManager::tileWidth() {
    return tileW;
} 

unsigned int TileManager::tileHeight() {
    return tileH;
} 

TEABAG_INTERNAL_END

TEABAG_NS_END
