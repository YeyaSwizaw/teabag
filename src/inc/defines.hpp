#ifndef TEABAG_DEFINES_HPP
#define TEABAG_DEFINES_HPP

#define TEABAG_NAMESPACE_BEGIN namespace teabag {
#define TEABAG_NAMESPACE_END }

#define TEABAG_MAIN_FILE "data/main.tea" 
#define TEABAG_MAP_TEXTFILE(map_name) "data/maps/" + map_name + ".tea"
#define TEABAG_MAP_IMGFILE(map_name) "data/maps/" + map_name + ".png"
#define TEABAG_TILE_FILE(tile_name) "data/tiles/" + tile_name + ".png"

#define TEABAG_DEFAULT_NAME "Teabag Engine"

#define TEABAG_DEFAULT_TILE_SIZE 32

#define TEABAG_ERROR(tea_err_str) std::cout << "Error: " << tea_err_str << "\n";
#define TEABAG_FILE_NOT_FOUND(file) TEABAG_ERROR(std::string("File \"") + file + std::string("\" not found"));
#define TEABAG_LOG(tea_log_str) std::cout << "Log: " << tea_log_str << "\n";

#endif // TEABAG_DEFINES_HPP
