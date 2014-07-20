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
//// File: src/inc/game.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_GAME_HPP
#define TEABAG_GAME_HPP
 
#include "defines.hpp"
#include "error.hpp"
#include "reader.hpp"
#include "signal.hpp"
#include "world.hpp"
#include "ui.hpp"
#include "view.hpp"

#include <SFML/Graphics.hpp>

TEABAG_NS

/**
 * The base class for a game.
 * This class is the starting point for anything created with the teabag
 * engine. It contains functions to manage initialisation, events, entities,
 * and the game map.
 */
class TEABAG_API Game {
public:
	/**
	 * Initialises the game.
	 * This reads the main game definition file, and initialises the window.
     * 
     * @throws Error on failure - error reading file, initialising SFML etc. 
	 */
    void init();

    /**
     * Returns the attached signals struct.
     */
    GameSignals& signals();

    /**
     * Returns a reference to the world object, for access to the map, entities
     * etc.
     */
    World& world();

    /**
     * Returns a reference to the view object, for access to view scrolling /
     * resizing.
     */
    View& view();

    /**
     * Returns a reference to the ui object, for access to ui elements such as 
     * labels.
     */
    UI& ui();

    /**
	 * Runs the game.
	 * Starts the main loop, calling tick callbacks every loop, event callbacks
	 * when the relevant events happen, and collision callbacks when the 
	 * relevant objects collide.
     */
    void run();

    /**
     * Exits the game
     */
    void exit();

private:
    GameSignals sigs;
    World w;
    View v;
};

TEABAG_NS_END

#endif
