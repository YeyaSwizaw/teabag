#ifndef TEABAG_WORLD_HPP
#define TEABAG_WORLD_HPP

#include "defines.hpp"
#include "reader.hpp"
#include "error.hpp"
#include "map.hpp"
#include "entitymanager.hpp"
#include "entity.hpp"
#include "signal.hpp"

#include <string>
#include <unordered_map>

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
     * Returns the attached signals struct.
     */
    WorldSignals& signals();

    /**
     * Returns a reference to the given entity, if found.
     * Otherwise throws an exception.
     */
    Entity& entity(std::string name);

    /**
     * Returns the value of a loaded option
     */
    std::string option(std::string name);

private:
    friend class Game;

    void render(sf::RenderWindow& window);

    void checkCollisions();

    Map map;
    internal::EntityManager entityManager;

    WorldSignals sigs;
    std::unordered_map<std::string, std::string> opts;

    bool justLoaded;
};

TEABAG_NS_END

#endif
