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
//// File: src/inc/entitymanager.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_ENTITYMANAGER_HPP
#define TEABAG_ENTITYMANAGER_HPP

#include "defines.hpp"
#include "reader.hpp"
#include "error.hpp"
#include "entity.hpp"

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

#include <SFML/Graphics.hpp>

TEABAG_NS

class World;

TEABAG_INTERNAL

struct EntityInfo {
    std::string name;
    int x, y;
}; 

class EntityManager {
private:
    friend class teabag::World;

    EntityManager();

    void queueEntity(std::string name, int x, int y);
    void loadQueue();
    void loadEntity(EntityInfo& entity);
    Entity& loadAdditionalEntity(std::string name, int x, int y, std::string sprite);
    void loadTexture(std::string name);

    std::vector<EntityInfo> entityQueue;

    std::unordered_map<std::string, Texture> textures;
    std::unordered_map<std::string, teabag::Entity> entities;
};

TEABAG_INTERNAL_END

TEABAG_NS_END

#endif
