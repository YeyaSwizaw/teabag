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
//// File: src/anchor.cpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#include "inc/anchor.hpp"

TEABAG_NS

TEABAG_INTERNAL

WindowAnchor::WindowAnchor(Type type, int offset)
    : type(type), offset(offset) {}

int WindowAnchor::calculate(int itemW, int itemH, int winW, int winH) {
    switch(type) {
        case Top:
            return offset;

        case Bottom:
            return winH - itemH - offset;

        case Left:
            return offset;

        case Right:
            return winW - itemW - offset;
    } 
} 


ItemAnchor::ItemAnchor(Type type, int offset, teabag::Label& anchor)
    : type(type), offset(offset), anchor(anchor) {}

int ItemAnchor::calculate(int itemW, int itemH, int winW, int winH) {
    const auto& bounds = anchor.text.getGlobalBounds();

    switch(type) {
        case Top:
            return bounds.top - itemH - offset;

        case Bottom:
            return bounds.top + bounds.height + offset;

        case Left:
            return bounds.left - itemW - offset;

        case Right:
            return bounds.left + bounds.width + offset;
    } 
}

TEABAG_INTERNAL_END

TEABAG_NS_END


