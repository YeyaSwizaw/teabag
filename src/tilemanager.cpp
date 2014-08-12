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
//// File: src/tilemanager.cpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#include "inc/tilemanager.hpp"

TEABAG_NS

TEABAG_INTERNAL

TileManager::TileManager() 
    : colours(10, [](sf::Color c) { return std::hash<int>()(c.r + 255 * (c.g + 255 * (c.b))); }),
      tileW(0), tileH(0) {}

void TileManager::queueTile(std::string name, int r, int g, int b) {
    tileQueue.push_back({name, r, g, b});
} 

void TileManager::loadQueue() {
    tiles.clear();
    colours.clear();

    for(TileInfo& tile : tileQueue) {
        loadTile(tile);
    } 

    tileQueue.clear();
} 

void TileManager::loadTile(TileInfo& tile) {
    std::string texfile = TEABAG_TILE_IMG(tile.name);

    sf::Texture tex;
    if(!tex.loadFromFile(texfile)) {
        throw FileOpenError(texfile);
    } 

    bool blocking = true;
    int x0 = 0;
    int y0 = 0;
    int x1 = tex.getSize().x;
    int y1 = tex.getSize().y;

    std::string file = TEABAG_TILE_TEA(tile.name);
    internal::Reader reader(file);
    if(reader) {
        while(reader.nextLine()) {
            std::string option;
            if(!reader.get(option)) {
                throw LineReadError(file, reader.line);
            } 
            
            if(option == "blocking") {
                if(!reader.get(blocking)) {
                    throw LineReadError(file, reader.line);
                } 
            }
            else if(option == "rect") {
                if(!reader.get(x0, y0, x1, y1)) {
                    throw LineReadError(file, reader.line);
                } 
            } 
        } 
    }  

    tiles[tile.name] = {tile.name, sf::Color(tile.r, tile.g, tile.b), blocking, tex, x0, x1, y0, y1};
    colours[tiles[tile.name].colour] = tile.name;

    tileW = std::max(tileW, tex.getSize().x);
    tileH = std::max(tileH, tex.getSize().y);
} 

const Tile& TileManager::tileFromName(std::string name) {
    return tiles[name];
} 

const Tile& TileManager::tileFromColour(sf::Color colour) {
    return tiles[colours[colour]];
} 

unsigned int TileManager::tileWidth() {
    return tileW;
} 

unsigned int TileManager::tileHeight() {
    return tileH;
} 

TEABAG_INTERNAL_END

TEABAG_NS_END
