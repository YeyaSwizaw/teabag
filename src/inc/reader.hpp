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
//// File: src/inc/reader.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_READER_HPP
#define TEABAG_READER_HPP

#include "defines.hpp"

#include <string>
#include <fstream>
#include <sstream>

TEABAG_NS

class Game;
class World;

TEABAG_INTERNAL

class EntityManager;

/**
 * Reads files one token at a time.
 * Used internally to parse .tea files.
 */
class Reader {
private:
    friend class teabag::Game;
    friend class teabag::World;
    friend class EntityManager;

    Reader(std::string filename);
    ~Reader();

    explicit operator bool() const;

    bool nextLine();
    template<typename T> bool get(T& t);
    template<typename T, typename ...Args> bool get(T& t, Args& ...args);

    std::ifstream file;
    std::string line;
    std::istringstream linestream;
};

template<typename T>
bool Reader::get(T& t) {
    return (linestream >> t);
} 

template<typename T, typename ...Args> 
bool Reader::get(T& t, Args& ...args) {
    return (linestream >> t) && get(args...);
} 

TEABAG_INTERNAL_END

TEABAG_NS_END

#endif
