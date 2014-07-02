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
//// File: src/reader.cpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#include "inc/reader.hpp"

TEABAG_NS

TEABAG_INTERNAL

Reader::Reader(std::string filename) {
    file.open(filename);
} 

Reader::~Reader() {
    file.close();
} 

Reader::operator bool() const {
    return file.is_open();
} 

bool Reader::nextLine() {
    line.clear();
    linestream.clear();
    while(std::getline(file, line)) {
        if(!line.empty()) {
            linestream.str(line);
            return true;
        } 
    } 

    return false;
} 

TEABAG_INTERNAL_END

TEABAG_NS_END
