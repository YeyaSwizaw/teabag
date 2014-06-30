#ifndef TEABAG_COLLISION_HPP
#define TEABAG_COLLISION_HPP

#include "defines.hpp"

#include <string>

#include <SFML/Graphics.hpp>

TEABAG_NS

class Collision {
public:
    enum Type {
        Entity,
        Tile
    }; 

    const sf::FloatRect collisionBounds;
    const sf::FloatRect targetBounds;

    const Type type;
    const std::string targetName;
};

TEABAG_NS_END

#endif
