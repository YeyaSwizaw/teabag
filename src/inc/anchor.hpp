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
//// File: src/inc/anchor.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_ANCHOR_HPP
#define TEABAG_ANCHOR_HPP

#include "defines.hpp"
#include "label.hpp"

#include <SFML/Graphics.hpp>

TEABAG_NS

class UI;
class Label;

TEABAG_INTERNAL

class Anchor {
protected:
    friend class teabag::UI;
    friend class teabag::Label;

    enum Type {
        Top, Bottom, Left, Right
    }; 

    virtual int calculate(int itemW, int itemH, int winW, int winH) = 0;
}; 

class WindowAnchor : public Anchor {
private:
    friend class teabag::UI;
    friend class teabag::Label;

    WindowAnchor(Type type, int offset);

    Type type;
    int offset;

    virtual int calculate(int itemW, int itemH, int winW, int winH);
}; 

class ItemAnchor : public Anchor {
private:
    friend class teabag::UI;
    friend class teabag::Label;

    ItemAnchor(Type type, int offset, teabag::Label& anchor);

    Type type;
    int offset;
    teabag::Label& anchor;

    virtual int calculate(int itemW, int itemH, int winW, int winH);
}; 

TEABAG_INTERNAL_END

TEABAG_NS_END

#endif
