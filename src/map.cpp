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
//// File: src/map.cpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#include "inc/map.hpp"

TEABAG_NS

void Map::loadMap(std::string name) {
    std::string filename = TEABAG_MAP_IMG(name);

    sf::Image img;
    if(!img.loadFromFile(filename)) {
        throw FileOpenError(filename);
    } 

    map = std::vector<std::vector<std::string>>();

    for(unsigned int x = 0; x < img.getSize().x; ++x) {
        map.push_back(std::vector<std::string>());

        for(unsigned int y = 0; y < img.getSize().y; ++y) {
            sf::Color c = img.getPixel(x, y);
            map.back().push_back(tileManager.tileFromColour(c).name);
        } 
    } 

    rendTex.create(map.size() * tileManager.tileWidth(), map[0].size() * tileManager.tileHeight());
    rendTex.clear();

    for(decltype(map)::size_type x = 0; x < map.size(); ++x) {
        for(decltype(map)::size_type y = 0; y < map[x].size(); ++y) {
            const Tile& t = tileManager.tileFromName(map[x][y]);

            sf::Sprite spr;
            spr.setTexture(t.tex);
            spr.setPosition(x * t.tex.getSize().x, y * t.tex.getSize().y);
            rendTex.draw(spr);
        } 
    } 

    rendTex.display();
    mapSprite.setTexture(rendTex.getTexture());
    mapSprite.setPosition(0, 0);
} 

internal::TileManager& Map::tiles() {
    return tileManager;
} 

TEABAG_NS_END
