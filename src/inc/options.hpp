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
//// File: src/inc/options.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_OPTIONS_HPP
#define TEABAG_OPTIONS_HPP

#include "defines.hpp"

#include <string>
#include <unordered_map>

TEABAG_NS

/**
 * Class containing options for a class
 */
class TEABAG_API Options {
public:
    /**
     * Returns true if the class has a sepecific option defined.
     */
    bool has(std::string key);

    /**
     * Returns the value for a specific option, or an empty string 
     * if the option does not exist.
     */
    std::string get(std::string key);

    /**
     * Sets the value for a specific option.
     */
    void set(std::string key, std::string value);

private:
    std::unordered_map<std::string, std::string> values;
}; 

TEABAG_INTERNAL

class TEABAG_API HasOptions {
public:
    /**
     * Gets the object containing the options for a class.
     */
    Options& options();

protected:
    Options optionsObj;

    void setOption(std::string key, std::string value);
};

TEABAG_INTERNAL_END

TEABAG_NS_END

#endif
