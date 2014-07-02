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
//// File: src/inc/error.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_ERROR_HPP
#define TEABAG_ERROR_HPP

#include "defines.hpp"

#include <string>

TEABAG_NS

class Error {
public:
    Error(std::string msg);

    std::string message();

private:
    std::string msg;
};

class FileOpenError : public Error {
public:
    FileOpenError(std::string file);
}; 

class LineReadError : public Error {
public:
    LineReadError(std::string file, std::string line);
}; 

class NoSuchEntityError : public Error {
public:
    NoSuchEntityError(std::string name);
}; 

class NoSuchOptionError : public Error {
public:
    NoSuchOptionError(std::string name);
}; 

TEABAG_NS_END

#endif
