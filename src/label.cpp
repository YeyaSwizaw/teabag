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
//// File: src/label.cpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#include "inc/label.hpp"

TEABAG_NS

Label::Label()
    : horizontalAnchor(nullptr), verticalAnchor(nullptr) {}

Label::Label(internal::Anchor* horizontalAnchor, internal::Anchor* verticalAnchor, sf::Font& font, int size)
    : horizontalAnchor(horizontalAnchor), verticalAnchor(verticalAnchor), changed(true) {

    text.setFont(font);
    text.setCharacterSize(size);
} 

void Label::set(std::string string) {
    text.setString(string);
    changed = true;
} 

void Label::recalculate(sf::RenderWindow& window) {
    int x = 0;
    int y = 0;
    int w = text.getGlobalBounds().width;
    int h = text.getGlobalBounds().height;

    int winW = window.getSize().x;
    int winH = window.getSize().y;

    if(horizontalAnchor) {
        x = horizontalAnchor->calculate(w, h, winW, winH);
    } 

    if(verticalAnchor) {
        y = verticalAnchor->calculate(w, h, winW, winH);
    } 

    text.setPosition(x, y);
    changed = false;
} 

TEABAG_NS_END
