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
//// File: src/inc/label.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_LABEL_HPP
#define TEABAG_LABEL_HPP

#include "defines.hpp"
#include "anchor.hpp"
#include "fontmanager.hpp"

#include <memory>

#include <SFML/Graphics.hpp>

TEABAG_NS

class UI;

TEABAG_INTERNAL

class Anchor;
class ItemAnchor;

TEABAG_INTERNAL_END

class Label {
public:
    Label();

    /**
     * Sets the label text. This triggers a recalculation of the position of this
     * and all following items.
     */
    void set(std::string string);

private:
    friend class UI;
    friend class internal::ItemAnchor;

    Label(internal::Anchor* horizontalAnchor, internal::Anchor* verticalAnchor, sf::Font& font, int size);
    void recalculate(sf::RenderWindow& window);

    std::shared_ptr<internal::Anchor> horizontalAnchor, verticalAnchor;
    sf::Text text;

    bool changed;
};

TEABAG_NS_END

#endif
