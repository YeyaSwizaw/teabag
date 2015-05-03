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
//// File: src/ui.cpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#include "inc/ui.hpp"

TEABAG_NS

void UI::loadUi(std::string name) {
    std::string file = TEABAG_UI_TEA(name);

    internal::Reader reader(file);
    if(!reader) {
        throw FileOpenError(file);
    } 

    while(reader.nextLine()) {
        std::string option;
        if(!reader.get(option)) {
            throw LineReadError(file, reader.line);
        } 

        if(option == "font") {
            std::string name, font;
            int size;

            if(!reader.get(name, font, size)) {
                throw LineReadError(file, reader.line);
            } 

            fonts.queueFont(name, font, size);
        } 

        else if(option == "label") {
            std::string name, font, ver, hor;
            int voff, hoff;

            if(!reader.get(name, font, ver, voff, hor, hoff)) {
                throw LineReadError(file, reader.line);
            } 

            queueItem(name, font, ver, voff, hor, hoff);
        } 
    } 

    fonts.loadQueue();
    loadItems();
} 

void UI::queueItem(std::string name, std::string font, std::string vert, int voff, std::string hor, int hoff) {
    itemQueue.push_back({name, font, vert, hor, voff, hoff});
} 

void UI::loadItems() {
    for(internal::ItemInfo& info : itemQueue) {
        loadItem(info);
    } 

    itemQueue.clear();
} 

void UI::loadItem(internal::ItemInfo& info) {
    if(fonts.fonts.find(info.font) == fonts.fonts.end()) {
        throw NoSuchFontError(info.font);
    } 

    std::regex re("(.*)\\.(.*)");
    std::cmatch res;

    internal::Anchor* verticalAnchor = nullptr;
    internal::Anchor* horizontalAnchor = nullptr;

    // Vertical anchor
    if(std::regex_search(info.verticalAnchor.c_str(), res, re)) {
        std::string targetItem = res[1];
        std::string side = res[2];

        if(items.find(targetItem) == items.end() || !(side == "top" || side == "bottom")) {
            throw InvalidAnchor(info.verticalAnchor, true);
        } 

        verticalAnchor = new internal::ItemAnchor(
                side == "top" ? internal::Anchor::Top : internal::Anchor::Bottom,
                info.vertcalOffset, items[targetItem]);

    } else {
        if(!(info.verticalAnchor == "top" || info.verticalAnchor == "bottom")) {
            throw InvalidAnchor(info.verticalAnchor, true);
        } 

        verticalAnchor = new internal::WindowAnchor(
            info.verticalAnchor == "top" ? internal::Anchor::Top : internal::Anchor::Bottom,
            info.vertcalOffset);
    } 

    // Horizontal anchor
    if(std::regex_search(info.horizontalAnchor.c_str(), res, re)) {
        std::string targetItem = res[1];
        std::string side = res[2];

        if(items.find(targetItem) == items.end() || !(side == "left" || side == "right")) {
            throw InvalidAnchor(info.horizontalAnchor, true);
        } 

        horizontalAnchor = new internal::ItemAnchor(
                side == "left" ? internal::Anchor::Left : internal::Anchor::Right,
                info.horizontalOffset, items[targetItem]);

    } else {
        if(!(info.horizontalAnchor == "left" || info.horizontalAnchor == "right")) {
            throw InvalidAnchor(info.horizontalAnchor, false);
        } 

        horizontalAnchor = new internal::WindowAnchor(
            info.horizontalAnchor == "left" ? internal::Anchor::Left : internal::Anchor::Right,
            info.horizontalOffset);
    } 

    items[info.name] = {horizontalAnchor, verticalAnchor, fonts.fontFiles[fonts.fonts[info.font].font], fonts.fonts[info.font].size};
    itemOrder.push_back(info.name);
} 

void UI::render(sf::RenderWindow& window, bool recalculate) {
    for(std::string& name : itemOrder) {
        teabag::Label& label = items[name];
        recalculate = recalculate || label.changed;

        if(recalculate) {
            label.recalculate(window);
        } 

        window.draw(label.text);
    } 
} 

Label& UI::label(std::string name) {
    if(items.find(name) == items.end()) {
        throw NoSuchLabelError(name);
    } 

    return items.at(name);
} 

TEABAG_NS_END
