////////////////////////////////////////////////////////////////////////////////
//// Copyright 2014 Samuel Sleight
////
//// Licensed under the Apache License, Version 2.0 (the "License");
//// you may not use this file except in compliance with the License.
//// You may obtain a copy of the License at
////
//// 		http://www.apache.org/licenses/LICENSE-2.0
////
//// Unless required by applicable law or agreed to in writing, software
//// distributed under the License is distributed on an "AS IS" BASIS,
//// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//// See the License for the specific language governing permissions and
//// limitations under the License.
///////////////////////////////////////////////////////////////////////////////
//// Project: Teabag
//// File: src/inc/world.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_WORLD_HPP
#define TEABAG_WORLD_HPP

#include "defines.hpp"
#include "reader.hpp"
#include "error.hpp"
#include "map.hpp"
#include "entitymanager.hpp"
#include "entity.hpp"
#include "signal.hpp"

#include <chrono>
#include <random>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

TEABAG_NS

class Game;

/**
 * This class stores everything about the game world - map,
 * entities, etc.
 */
class TEABAG_API World {
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
     * Loads a new entity, placing it at the given position and using the
     * given sprite.
     * If no name is given, a random one is generated.
     * @return A reference to the new entity.
     */
    Entity& newEntity(std::string name, int x, int y, std::string sprite);
    Entity& newEntity(int x, int y, std::string sprite);

    /**
     * Returns the value of a loaded option
     */
    std::string option(std::string name);

private:
    friend class Game;

    World();

    void render(sf::RenderWindow& window);

    void checkCollisions();

    std::mt19937 rndEng;

    Map map;
    internal::EntityManager entityManager;

    WorldSignals sigs;
    std::unordered_map<std::string, std::string> opts;

    bool justLoaded;
};

TEABAG_NS_END

#endif
