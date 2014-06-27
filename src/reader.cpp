#include "inc/reader.hpp"

TEABAG_NS

TEABAG_INTERNAL

Reader::Reader(std::string filename) {
    file.open(filename);
} 

Reader::~Reader() {
    file.close();
} 

Reader::operator bool() const {
    return file.is_open();
} 

bool Reader::nextLine() {
    line.clear();
    linestream.clear();
    while(std::getline(file, line)) {
        if(!line.empty()) {
            linestream.str(line);
            return true;
        } 
    } 

    return false;
} 

TEABAG_INTERNAL_END

TEABAG_NS_END
