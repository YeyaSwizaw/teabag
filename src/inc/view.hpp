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
//// File: src/inc/view.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_VIEW_HPP
#define TEABAG_VIEW_HPP

#include "defines.hpp"
#include "ui.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

TEABAG_NS

class Game;

class View {
public:
    /**
     * Resizes the view.
     */
    void resize(int w, int h);

    /**
     * Scrolls the view.
     */
    void scroll(int x, int y);

    /**
     * Centers the view on a location.
     */
    void centerOn(int x, int y);

    /**
     * Gets the x position of the mouse.
     */
    int mouseX() const;

    /**
     * Gets the y position of the mouse.
     */
    int mouseY() const;

    /**
     * Gets the x position of the view center
     */
    int x() const;

    /**
     * Gets the y position of the view center
     */
    int y() const;

    /**
     * Gets the view width
     */
    int w() const;

    /**
     * Gets the view height
     */
    int h() const;

private:
    friend class Game;

    sf::RenderWindow window;
    UI ui;
};

TEABAG_NS_END

#endif
