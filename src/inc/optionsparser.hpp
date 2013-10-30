#ifndef TEABAG_OPTIONSPARSER_HPP
#define TEABAG_OPTIONSPARSER_HPP

#include "defines.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

TEABAG_NS

class Game;

/**
 * Parses options files.
 * This class is used internally to parse .tea files.
 */
class OptionsParser {
private:
	friend class Game;

	OptionsParser(std::string filename);
	~OptionsParser();

	explicit operator bool() const;

	bool nextOption();

	std::ifstream file;
	std::string line;

}; // class OptionsParser;

TEABAG_NS_END

#endif // TEABAG_OPTIONSPARSER_HPP
