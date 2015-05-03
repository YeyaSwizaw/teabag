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
//// File: src/error.cpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#include "inc/error.hpp"

TEABAG_NS

// Base Error Class
Error::Error(std::string msg)
    : msg(msg) {}

std::string Error::message() {
    return msg;
} 

// File Opening Error
FileOpenError::FileOpenError(std::string file) 
    : Error("Unable to open file: " + file) {}

// File Reading Error
LineReadError::LineReadError(std::string file, std::string line)
    : Error("Unable to read file: " + file + "\nError reading line:\n" + line) {}

// No Such Entity Error
NoSuchEntityError::NoSuchEntityError(std::string name)
    : Error("No such entity in world: " + name) {}

// No Such Option Error
NoSuchOptionError::NoSuchOptionError(std::string name)
    : Error("No such option in world: " + name) {}

// No Such Font Error
NoSuchFontError::NoSuchFontError(std::string name) 
    : Error("No such font: " + name) {}

// No Such Label Error
NoSuchLabelError::NoSuchLabelError(std::string name)
    : Error("No such UI label: " + name) {}

// Invalid UI Anchor Error
InvalidAnchor::InvalidAnchor(std::string name, bool vertical)
    : Error("'" + name + "' is an invalid " + (vertical ? "vertical" : "horizontal") + "anchor") {}

TEABAG_NS_END
