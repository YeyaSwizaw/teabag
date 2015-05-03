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
//// File: src/inc/fontmanager.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_FONTMANAGER_HPP
#define TEABAG_FONTMANAGER_HPP

#include "defines.hpp"
#include "error.hpp"

#include <string>
#include <vector>
#include <unordered_map>

#include <SFML/Graphics.hpp>

TEABAG_NS

class UI;

TEABAG_INTERNAL

struct FontInfo {
    std::string name, font;
    int size;
}; 

class FontManager {
private:
    friend class teabag::UI;

    void queueFont(std::string name, std::string font, int size);
    void loadQueue();
    void loadFont(FontInfo& info);

    std::vector<FontInfo> queue;

    std::unordered_map<std::string, sf::Font> fontFiles;
    std::unordered_map<std::string, FontInfo> fonts;
};

TEABAG_NS_END

TEABAG_INTERNAL_END

#endif
