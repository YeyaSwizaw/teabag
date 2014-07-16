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
//// File: src/inc/entity.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_ENTITY_HPP
#define TEABAG_ENTITY_HPP

#include "defines.hpp"
#include "signal.hpp"

#include <SFML/Graphics.hpp>

TEABAG_NS

class World;

TEABAG_INTERNAL

class EntityManager;

struct Texture {
    sf::Texture tex;
    int spriteWidth, spriteHeight;
}; 

TEABAG_INTERNAL_END

/**
 * This class represents an entity in the game world.
 */
class TEABAG_API Entity {
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
     * Sets the current sprite from the spritesheet. x and y are the coordinates
     * of the sprite in the grid of sprites.
     */
    void setSpriteCoord(int x, int y);

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

    Entity(std::string name, int x, int y, internal::Texture& tex);

    EntitySignals sigs;

    std::string name;

    sf::Sprite sprite;
};

TEABAG_NS_END

#endif
