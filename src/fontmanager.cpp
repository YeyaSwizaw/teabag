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
//// File: src/fontmanager.cpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#include "inc/fontmanager.hpp"

TEABAG_NS

TEABAG_INTERNAL

void FontManager::queueFont(std::string name, std::string font, int size) {
    queue.push_back({name, font, size});
}

void FontManager::loadQueue() {
    fontFiles.clear();
    fonts.clear();

    for(FontInfo& info : queue) {
        loadFont(info);
    } 

    queue.clear();
} 

void FontManager::loadFont(FontInfo& info) {
    if(fontFiles.find(info.font) == fontFiles.end()) {
        std::string file = TEABAG_FONT(info.font);
        sf::Font font;
        if(!font.loadFromFile(file)) {
            throw teabag::FileOpenError(file);
        } 

        fontFiles[info.font] = font;
    } 

    fonts[info.name] = info;
} 

TEABAG_INTERNAL_END

TEABAG_NS_END
