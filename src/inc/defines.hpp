#ifndef TEABAG_DEFINES_HPP
#define TEABAG_DEFINES_HPP

#define TEABAG_NS namespace teabag {
#define TEABAG_NS_END }

#define TEABAG_DEF_NAME "Teabag Engine"

#define TEABAG_DEF_WIN_WIDTH 800
#define TEABAG_DEF_WIN_HEIGHT 600

#define TEABAG_MAIN_FILE "data/main.tea"
#define TEABAG_MAP_TEA(name) "data/maps/" + name + ".tea"

#define TEABAG_ERROR(msg) std::cout << "Error: " << msg << std::endl

#define TEABAG_FILE_OPEN_ERROR(file) TEABAG_ERROR("Unable to open file: \"" + file + "\"")
#define TEABAG_FILE_PARSE_ERROR(file, line) TEABAG_ERROR("Parse error in file: \"" + file + "\", line: \"" + line + "\"")

#endif // TEABAG_DEFINES_HPP
