#include "inc/optionsparser.hpp"

TEABAG_NS

OptionsParser::OptionsParser(std::string filename) {
	file.open(filename);

} // OptionsParser::OptionsParser(std::string filename);

OptionsParser::~OptionsParser() {
	file.close();

} // OptionsParser::~OptionsParser();

OptionsParser::operator bool() const {
	return file.is_open();

} // OptionsParser::operator bool();

bool OptionsParser::nextOption() {
	line.clear();
	while(std::getline(file, line)) {
		if(!line.empty()) {
			return true;

		} // if(!line.empty());

	} // while(std::getline(file, str));

	return false;

} // bool OptionsParser::nextOption();

TEABAG_NS_END
