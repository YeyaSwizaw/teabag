#ifndef TEABAG_OPTIONSPARSER_HPP
#define TEABAG_OPTIONSPARSER_HPP

#include "defines.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

TEABAG_NS

class Game;
class GameMap;
class EntityManager;

TEABAG_INTERNAL

/**
 * Parses options files.
 * This class is used internally to parse .tea files.
 */
class OptionsParser {
private:
	friend class teabag::Game;
	friend class GameMap;
	friend class EntityManager;

	OptionsParser(std::string filename);
	~OptionsParser();

	explicit operator bool() const;

	bool nextLine();
	template<typename T> bool get(T& t);

	std::ifstream file;
	std::string line;
	std::istringstream linestream;

}; // class OptionsParser;

template<typename T>
bool OptionsParser::get(T& t) {
	return (linestream >> t);

} // bool OptionsParser::get(T& t);

TEABAG_INTERNAL_END

TEABAG_NS_END

#endif // TEABAG_OPTIONSPARSER_HPP
