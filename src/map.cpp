#include "inc/map.hpp"

TEABAG_NS

GameMap::GameMap() {

} // GameMap::GameMap();

int GameMap::loadMap(std::string mapname) {
	std::string filename = TEABAG_MAP_TEA(mapname);
	OptionsParser parser(filename);
	if(!parser) {
		TEABAG_FILE_OPEN_ERROR(filename);
		return -1;

	} // if(!parser);

	while(parser.nextLine()) {
		std::string option;
		if(!parser.get(option)) {
			TEABAG_FILE_PARSE_ERROR(filename, parser.line);
			return -1;

		} // if(!parser.get(option));

		if(option == "tile") {
			int r, g, b;
			std::string name;
			bool collidable;

			if(!parser.get(r) || !parser.get(g) || !parser.get(b) || !parser.get(name) || !parser.get(collidable)) {
				TEABAG_FILE_PARSE_ERROR(filename, parser.line);
				return -1;

			} // if(!parser.get(r) || !parser.get(g) || !parser.get(name) || !parser.get(name) || !parser.get(collidable));

			std::cout << "Loaded Tile: " << name << ": " << r << ", " << g << ", " << b << " - " << collidable << std::endl;

		} // if(option == "tile");

	} // while(parser.nextLine());

	return 0;

} // int GameMap::loadMap(std::string mapname);

TEABAG_NS_END
