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
//// File: src/world.cpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#include "inc/world.hpp"

TEABAG_NS

World::World() {
    auto tp = std::chrono::system_clock::now();
    auto dur = tp.time_since_epoch();
    rndEng.seed(dur.count());
} 

void World::loadLevel(std::string name) {
    std::string file = TEABAG_MAP_TEA(name);

    internal::Reader reader(file);
    if(!reader) {
        throw FileOpenError(file);
    } 

    opts.clear();

    while(reader.nextLine()) {
        std::string option;
        if(!reader.get(option)) {
            throw LineReadError(file, reader.line);
        } 

        if(option == "tile") {
            int r, g, b;
            std::string name;

            if(!reader.get(r, g, b, name)) {
                throw LineReadError(file, reader.line);
            } 

            map.tiles().queueTile(name, r, g, b);
        } 
        else if(option == "entity") {
            std::string name;
            int x, y;

            if(!reader.get(name, x, y)) {
                throw LineReadError(file, reader.line);
            } 

            entityManager.queueEntity(name, x, y);
        } 
        else if(option == "option") {
            std::string name, value;

            if(!reader.get(name, value)) {
                throw LineReadError(file, reader.line);
            } 

            setOption(name, value);
        } 
    } 

    map.tiles().loadQueue();
    map.loadMap(name);

    entityManager.loadQueue();

    sigs.levelLoad().call(name);

    justLoaded = true;
} 

WorldSignals& World::signals() {
    return sigs;
} 

Entity& World::entity(std::string name) {
    if(entityManager.entities.find(name) == entityManager.entities.end()) {
        throw NoSuchEntityError(name);
    } 

    return entityManager.entities.at(name);
} 

Entity& World::newEntity(std::string name, int x, int y, std::string sprite) {
    return entityManager.loadAdditionalEntity(name, x, y, sprite);
} 

Entity& World::newEntity(int x, int y, std::string sprite) {
    std::ostringstream str;
    str << sprite << x << y;

    std::string name;
    do {
        name = str.str() + std::to_string(rndEng());
    } while(entityManager.entities.find(name) != entityManager.entities.end());

   return newEntity(name, x, y, sprite); 
} 

void World::render(sf::RenderWindow& window) {
    window.draw(map.mapSprite);

    for(auto& entityPair : entityManager.entities) {
        window.draw(entityPair.second.sprite);
    } 
}  

void World::tickActions() {
    for(auto& epair : entityManager.entities) {
        if(justLoaded) {
            break;
        } 

        epair.second.tick();
    } 
} 

void World::checkCollisions() {
    sf::FloatRect collRect;

    for(auto& e1pair : entityManager.entities) {
        if(justLoaded) {
            break;
        } 

        Entity& e1 = e1pair.second;

        // Entity collision
        for(auto& e2pair : entityManager.entities) {
            Entity& e2 = e2pair.second;

            if(e1.name != e2.name) {
                if(e1.sprite.getGlobalBounds().intersects(e2.sprite.getGlobalBounds(), collRect)) {
                    e1.signals().collision().call({collRect, e2.sprite.getGlobalBounds(), Collision::Type::Entity, e2.name});

                    if(justLoaded) {
                        break;
                    } 
                } 
            } 
        } 

        if(justLoaded) {
            break;
        } 

        // Tile collision
        int x0 = e1.sprite.getGlobalBounds().left / map.tiles().tileWidth();
        int y0 = e1.sprite.getGlobalBounds().top / map.tiles().tileHeight();

        int offsetX = (e1.sprite.getGlobalBounds().left - map.mapSprite.getGlobalBounds().left) / map.tiles().tileWidth();
        int offsetY = (e1.sprite.getGlobalBounds().top - map.mapSprite.getGlobalBounds().top) / map.tiles().tileHeight();

        int x1 = x0 + (e1.sprite.getGlobalBounds().width / map.tiles().tileWidth()) + 2;
        int y1 = y0 + (e1.sprite.getGlobalBounds().height / map.tiles().tileHeight()) + 2;

        for(int x = (x0 > 0 ? x0 - 1 : 0); x < x1; ++x) {
            for(int y = (y0 > 0 ? y0 - 1 : 0); y < y1; ++y) {
                int tx = offsetX + (x - x0);
                int ty = offsetY + (y - y0);

                if(tx >= 0 && ty >= 0 && tx < map.map.size() && ty < map.map[0].size()) {
                    const Tile& tile = map.tiles().tileFromName(map.map[tx][ty]);
                    if(tile.blocking) {
                        sf::FloatRect tileRect(
                            (tx * map.tiles().tileWidth()) + map.mapSprite.getGlobalBounds().left + tile.x0,
                            (ty * map.tiles().tileHeight()) + map.mapSprite.getGlobalBounds().top + tile.y0,
                            tile.x1, tile.y1);

                        if(e1.sprite.getGlobalBounds().intersects(tileRect, collRect)) {
                            e1.signals().collision().call({collRect, tileRect, Collision::Type::Tile, map.map[tx][ty]});

                            if(justLoaded) {
                                break;
                            } 
                        } 
                    } 
                } 
            } 

            if(justLoaded) {
                break;
            } 
        } 
    } 
} 

TEABAG_NS_END
