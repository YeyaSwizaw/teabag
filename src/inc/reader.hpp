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
