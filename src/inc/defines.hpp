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
//// File: src/inc/defines.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_DEFINES_HPP
#define TEABAG_DEFINES_HPP

#define TEABAG_NS namespace teabag {
#define TEABAG_NS_END }

#define TEABAG_INTERNAL namespace internal {
#define TEABAG_INTERNAL_END }

#define TEABAG_DEFAULT_NAME "Teabag"
#define TEABAG_DEFAULT_WINDOW_W 500
#define TEABAG_DEFAULT_WINDOW_H 500

#define TEABAG_MAIN_FILE "data/main.tea"
#define TEABAG_MAP_TEA(name) "data/maps/" + name + ".tea"
#define TEABAG_MAP_IMG(name) "data/maps/" + name + ".png"
#define TEABAG_TILE_TEA(name) "data/tiles/" + name + ".tea"
#define TEABAG_TILE_IMG(name) "data/tiles/" + name + ".png"
#define TEABAG_ENTITY_TEA(name) "data/entities/" + name + ".tea"
#define TEABAG_SPRITE_IMG(name) "data/sprites/" + name + ".png"
#define TEABAG_SPRITE_TEA(name) "data/sprites/" + name + ".tea"
#define TEABAG_UI_TEA(name) "data/ui/" + name + ".tea"
#define TEABAG_FONT(name) "data/ui/fonts/" + name

#ifdef _MSC_VER
 #ifdef TEABAG_EXPORT
  #define TEABAG_API __declspec(dllexport)
 #else
  #define TEABAG_API __declspec(dllimport)
 #endif
#else
 #define TEABAG_API
#endif

#endif
