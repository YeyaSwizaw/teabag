#ifndef TEABAG_TILE_HPP
#define TEABAG_TILE_HPP

#include "defines.hpp"

#include <string>

#include <SFML/Graphics.hpp>

TEABAG_NS

struct Tile {
    std::string name;
    sf::Color colour;
    bool blocking;
    sf::Texture tex;
};

TEABAG_NS_END

#endif
