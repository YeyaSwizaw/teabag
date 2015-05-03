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
//// File: src/options.cpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#include "inc/options.hpp"

TEABAG_NS

bool Options::has(std::string key) {
    return values.find(key) != values.end();
} 

std::string Options::get(std::string key) {
    auto it = values.find(key);

    if(it == values.end()) {
        return "";
    } else {
        return it->second;
    } 
} 

void Options::set(std::string key, std::string value) {
    values[key] = value;
} 

TEABAG_INTERNAL

Options& HasOptions::options() {
    return optionsObj;
} 

void HasOptions::setOption(std::string key, std::string value) {
    optionsObj.set(key, value);
} 

TEABAG_INTERNAL_END

TEABAG_NS_END

