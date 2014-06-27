#ifndef TEABAG_WORLD_HPP
#define TEABAG_WORLD_HPP

#include "defines.hpp"
#include "reader.hpp"
#include "error.hpp"
#include "map.hpp"
#include "entitymanager.hpp"
#include "entity.hpp"

#include <string>

#include <SFML/Graphics.hpp>

TEABAG_NS

class Game;

/**
 * This class stores everything about the game world - map,
 * entities, etc.
 */
class World {
public:
    /**
     * Clear the current level (if any) and load the provided.
     * This clears all entities, and so any entity signals need reattaching.
     */
    void loadLevel(std::string name);

    /**
     * Returns a reference to the given entity, if found.
     * Otherwise throws an exception.
     */
    Entity& entity(std::string name);

private:
    friend class Game;

    void render(sf::RenderWindow& window);

    Map map;
    internal::EntityManager entityManager;
};

TEABAG_NS_END

#endif
