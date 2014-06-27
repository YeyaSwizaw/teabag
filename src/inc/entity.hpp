#ifndef TEABAG_ENTITY_HPP
#define TEABAG_ENTITY_HPP

#include "defines.hpp"

#include <SFML/Graphics.hpp>

TEABAG_NS

class World;

TEABAG_INTERNAL

class EntityManager;

TEABAG_INTERNAL_END

/**
 * This class represents an entity in the game world.
 */
class Entity {
public:
    /**
     * Moves the entity
     */
    void move(int x, int y);

private:
    friend class internal::EntityManager;
    friend class World;

    Entity(int x, int y, sf::Texture& tex);

    sf::Sprite sprite;
};

TEABAG_NS_END

#endif
