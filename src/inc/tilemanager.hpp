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
//// File: src/inc/tilemanager.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_TILEMANAGER_HPP
#define TEABAG_TILEMANAGER_HPP

#include "defines.hpp"
#include "error.hpp"
#include "tile.hpp"
#include "reader.hpp"

#include <string>
#include <unordered_map>
#include <functional>
#include <utility>
#include <algorithm>

#include <SFML/Graphics.hpp>

TEABAG_NS

class World;
class Map;

TEABAG_INTERNAL

struct TileInfo {
    std::string name;
    int r, g, b;
}; 

class TileManager {
private:
    friend class teabag::World;
    friend class teabag::Map;

    TileManager();

    void queueTile(std::string name, int r, int g, int b);
    void loadQueue();
    void loadTile(TileInfo& tile);

    const Tile& tileFromName(std::string name);
    const Tile& tileFromColour(sf::Color colour);

    unsigned int tileWidth();
    unsigned int tileHeight();

    std::vector<TileInfo> tileQueue;

    std::unordered_map<std::string, Tile> tiles;
    std::unordered_map<sf::Color, std::string, std::function<size_t(sf::Color)>> colours;

    unsigned int tileW;
    unsigned int tileH;
};

TEABAG_INTERNAL_END

TEABAG_NS_END

#endif
