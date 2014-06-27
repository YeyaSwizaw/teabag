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

TEABAG_NS_END

#endif
