#ifndef TEABAG_ENTITY_HPP
#define TEABAG_ENTITY_HPP

#include "defines.hpp"
#include "signal.hpp"

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
     * Returns the attached signals struct.
     */
    EntitySignals& signals();

    /**
     * Moves the entity
     */
    void move(int x, int y);

    /**
     * Places the entity at a specific location
     */
    void place(int x, int y);

    /**
     * Gets the x position of the entity
     */
    int x() const;

    /**
     * Gets the y position of the entity
     */
    int y() const;

private:
    friend class internal::EntityManager;
    friend class World;

    Entity(std::string name, int x, int y, sf::Texture& tex);

    EntitySignals sigs;

    std::string name;

    sf::Sprite sprite;
};

TEABAG_NS_END

#endif
