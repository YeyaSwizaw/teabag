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
//// File: src/inc/ui.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_UI_HPP
#define TEABAG_UI_HPP

#include "defines.hpp"
#include "reader.hpp"
#include "error.hpp"
#include "fontmanager.hpp"
#include "anchor.hpp"
#include "label.hpp"

#include <string>
#include <regex>
#include <unordered_map>

#include <SFML/Graphics.hpp>

TEABAG_NS

TEABAG_INTERNAL

struct ItemInfo {
    std::string name;
    std::string font;
    std::string verticalAnchor, horizontalAnchor;
    int vertcalOffset, horizontalOffset;
}; 

TEABAG_INTERNAL_END

class World;

class TEABAG_API UI {
public:
    /**
     * Returns a reference to the requested label
     */
    Label& label(std::string name);

private:
    friend class World;

    void queue(std::string name);
    void load();

    void queueItem(std::string name, std::string font, std::string vert, int voff, std::string hor, int hoff);
    void loadItems();
    void loadItem(internal::ItemInfo& info);

    void draw(sf::RenderWindow& window);

    std::string queued;
    std::vector<internal::ItemInfo> itemQueue;

    std::unordered_map<std::string, teabag::Label> items;
    std::vector<std::string> itemOrder;
   
    internal::FontManager fonts; 
};

TEABAG_NS_END

#endif
