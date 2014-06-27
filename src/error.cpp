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

TEABAG_NS_END
