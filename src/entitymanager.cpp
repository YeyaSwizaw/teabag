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
//// File: src/entitymanager.cpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#include "inc/entitymanager.hpp"

TEABAG_NS

TEABAG_INTERNAL

EntityManager::EntityManager() {}

void EntityManager::queueEntity(std::string name, int x, int y) {
    entityQueue.push_back({name, x, y});
} 

void EntityManager::loadQueue() {
    entities.clear();
    textures.clear();

    for(EntityInfo& entity : entityQueue) {
        loadEntity(entity);
    } 

    entityQueue.clear();
} 

void EntityManager::loadEntity(EntityInfo& entity) {
    std::string file = TEABAG_ENTITY_TEA(entity.name);

    internal::Reader reader(file);
    if(!reader) {
        throw FileOpenError(file);
    } 

    std::string sprite;

    while(reader.nextLine()) {
        std::string option;
        if(!reader.get(option)) {
            throw LineReadError(file, reader.line);
        } 

        if(option == "sprite") {
            if(!reader.get(sprite)) {
                throw LineReadError(file, reader.line);
            } 
        } 
    } 

    if(textures.find(sprite) == textures.end()) {
        loadTexture(sprite);
    } 

    entities.insert({
        entity.name, {
            entity.name, entity.x, entity.y, textures[sprite], 
            [this, name=entity.name](){ this->entities.erase(name); }
    }});
} 

Entity& EntityManager::loadAdditionalEntity(std::string name, int x, int y, std::string sprite) {
    if(textures.find(sprite) == textures.end()) {
        loadTexture(sprite);
    } 

    entities.insert({
        name, {
            name, x, y, textures[sprite],
            [this, name](){ this->entities.erase(name); }
    }});

    return entities.at(name);
} 

void EntityManager::loadTexture(std::string name) {
    std::string file = TEABAG_SPRITE_IMG(name);

    sf::Texture tex;
    if(!tex.loadFromFile(file)) {
        throw FileOpenError(file);
    } 

    int w = tex.getSize().x;
    int h = tex.getSize().y;

    file = TEABAG_SPRITE_TEA(name);

    internal::Reader reader(file);
    if(reader) {
        while(reader.nextLine()) {
            std::string option;
            if(!reader.get(option)) {
                throw LineReadError(file, reader.line);
            } 

            if(option == "size") {
                if(!reader.get(w, h)) {
                    throw LineReadError(file, reader.line);
                } 
            } 
        } 
    } 

    textures.insert({name, {tex, w, h}});
}

TEABAG_INTERNAL_END

TEABAG_NS_END
