#ifndef TEABAG_MAP_HPP
#define TEABAG_MAP_HPP

#include "defines.hpp"
#include "tilemanager.hpp"
#include "error.hpp"

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

TEABAG_NS

class World;

/**
 * This class stores the level map and tiles.
 */
class Map {
private:
    friend class World;

    void loadMap(std::string name);

    internal::TileManager& tiles();

    internal::TileManager tileManager;
    std::vector<std::vector<std::string>> map;

    sf::RenderTexture rendTex;
    sf::Sprite mapSprite;
};

TEABAG_NS_END

#endif
