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
//// File: src/view.cpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#include "inc/view.hpp"

TEABAG_NS

void View::resize(int w, int h)  {
    sf::View view = window.getView();
    view.setSize(w, h);
    window.setView(view);
} 

void View::scroll(int x, int y) {
    sf::View view = window.getView();
    view.move(x, y);
    window.setView(view);
} 

void View::centerOn(int x, int y) {
    sf::View view = window.getView();
    view.setCenter(x, y);
    window.setView(view);
} 

int View::mouseX() const {
    return sf::Mouse::getPosition(window).x;
} 

int View::mouseY() const {
    return sf::Mouse::getPosition(window).y;
} 

int View::x() const {
    return window.getView().getCenter().x;
} 

int View::y() const {
    return window.getView().getCenter().y;
} 

int View::w() const {
    return window.getView().getSize().x;
} 

int View::h() const {
    return window.getView().getSize().y;
} 

TEABAG_NS_END
