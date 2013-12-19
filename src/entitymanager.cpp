#include "inc/entitymanager.hpp"

TEABAG_NS

TEABAG_INTERNAL

EntityManager::EntityManager() {

} // EntityManager::EntityManager();

EntityManager::~EntityManager() {

} // EntityManager::~EntityManager();

int EntityManager::addEntity(std::string name, int x, int y) {
	std::string filename = TEABAG_ENTITY_TEA(name);
	OptionsParser parser(filename);
	if(!parser) {
		TEABAG_FILE_OPEN_ERROR(filename);
		return -1;

	} // if(!parser);

	std::string sprname;

	while(parser.nextLine()) {
		std::string option;
		if(!parser.get(option)) {
			TEABAG_FILE_PARSE_ERROR(filename, parser.line);
			return -1;

		} // if(!parser.get(option));

		if(option == "sprite") {
			if(!parser.get(sprname)) {
				TEABAG_FILE_PARSE_ERROR(filename, parser.line);
				return -1;

			} // if(!parser.get(sprname));

		} // if(option == "sprite");

	} // while(parser.nextLine());

	if(texMap.find(sprname) == texMap.end()) {
		filename = TEABAG_ENTITY_IMG(name);

		sf::Texture tex;
		if(!tex.loadFromFile(filename)) {
			TEABAG_IMG_ERROR(filename);
			return -1;

		} // if(!tex.loadFromFile(filename));

		texMap.insert({sprname, tex});

	} // if(texMap.find(sprname) == texMap.end());

	entityMap[name] = Entity();
	entityMap[name].setPosition(x, y);
	entityMap[name].setTexture(texMap[sprname]);

	return 0;

} // int EntityManager::addEntity(std::string name, int x, int y);

TEABAG_INTERNAL_END

TEABAG_NS_END
