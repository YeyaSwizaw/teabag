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
//// File: src/inc/action.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_ACTION_HPP
#define TEABAG_ACTION_HPP

#include "defines.hpp"

TEABAG_NS

class Entity;

class Action {
public:
    virtual ~Action();

    virtual void start(Entity& entity) = 0;
    virtual bool tick(Entity& entity) = 0;
}; 

TEABAG_NS_END

#endif
