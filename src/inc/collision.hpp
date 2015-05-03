////////////////////////////////////////////////////////////////////////////////
//// Copyright 2014-2015 Samuel Sleight
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
//// File: src/inc/collision.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_COLLISION_HPP
#define TEABAG_COLLISION_HPP

#include "defines.hpp"

#include <string>

#include <SFML/Graphics.hpp>

TEABAG_NS

/**
 * This class holds information about a collision, including:
 * - The bounds of the collision.
 * - The bounds of the object collided with.
 * - Whether the object was a tile or another entity.
 * - The name of the object.
 */
class TEABAG_API Collision {
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
