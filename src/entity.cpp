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
//// File: src/entity.cpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#include "inc/entity.hpp"

TEABAG_NS

Entity::Entity(std::string name, int x, int y, internal::Texture& tex, std::function<void()> funcRemove)
    : name(name), funcRemove(funcRemove) {

    sprite.setPosition(x, y);
    sprite.setTexture(tex.tex);
    sprite.setTextureRect({0, 0, tex.spriteWidth, tex.spriteHeight});
} 

void Entity::move(int x, int y) {
    sprite.move(x, y);
} 

void Entity::place(int x, int y) {
    sprite.setPosition(x, y);
} 

void Entity::setSpriteCoord(int x, int y) {
    auto r = sprite.getTextureRect();
    sprite.setTextureRect({x * r.width, y * r.height, r.width, r.height});
} 

void Entity::remove() {
    funcRemove();
} 

EntitySignals& Entity::signals() {
    return sigs;
} 

int Entity::x() const {
    return sprite.getPosition().x;
} 

int Entity::y() const {
    return sprite.getPosition().y;
} 

int Entity::w() const {
    return sprite.getGlobalBounds().width;
} 

int Entity::h() const {
    return sprite.getGlobalBounds().height;
}

TEABAG_NS_END
