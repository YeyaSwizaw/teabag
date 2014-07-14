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
//// File: src/game.cpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#include "inc/game.hpp"

TEABAG_NS

void Game::init() {
    std::string file = TEABAG_MAIN_FILE;

    // Open file reader
    internal::Reader reader(file);
    if(!reader) {
        throw FileOpenError(file);
    } 

    std::string name = TEABAG_DEFAULT_NAME;
    unsigned int width = TEABAG_DEFAULT_WINDOW_W;
    unsigned int height = TEABAG_DEFAULT_WINDOW_H;

    // Parse main file
    while(reader.nextLine()) {
        std::string option;
        if(!reader.get(option)) {
            throw LineReadError(file, reader.line);
        } 

        if(option == "name") {
            name = reader.line.substr(5);
        }
        else if(option == "wind") {
            if(!reader.get(width, height)) {
                throw LineReadError(file, reader.line);
            } 
        } 
    } 

    // Create SFML window
    window.create(sf::VideoMode(width, height), name, sf::Style::Titlebar | sf::Style::Close);

    // #FIXME
    window.setFramerateLimit(60);
}

GameSignals& Game::signals() {
    return sigs;
} 

World& Game::world() {
    return w;
} 

UI& Game::ui() {
    return _ui;
} 

void Game::run() {
    while(window.isOpen()) {
        if(w.justLoaded) {
            w.justLoaded = false;
        }

        sigs.tick().call();

        sf::Event e;
        while(window.pollEvent(e)) {
            if(w.justLoaded) {
                break;
            } 

            sigs.handleEvent(e);
        } 

        if(w.justLoaded) {
            continue;
        } 

        w.checkCollisions();

        if(w.justLoaded) {
            continue;
        } 

        window.clear();
        w.render(window);
        _ui.render(window);
        window.display();
    } 
} 

void Game::resizeView(int w, int h) {
    window.setView(sf::View({0, 0, (float)w, (float)h}));
} 

void Game::exit() {
    window.close();
} 

TEABAG_NS_END
