#include "inc/sprman.hpp"

TEABAG_NAMESPACE_BEGIN

SpriteManager::SpriteManager() {

} // SpriteManager::SpriteManager();

int SpriteManager::loadSpritesheet(std::string name) {
	std::string filename = TEABAG_SPR_TEXTFILE(name);
	
	std::ifstream textfile(filename);

	if(!textfile) {
		TEABAG_FILE_NOT_FOUND(filename)
		return -1;

	} // if(!textfile);

	int x, y;

	std::string line;
	while(std::getline(textfile, line)) {
		std::istringstream lineStream(line);
		std::string value;

		lineStream >> value;

		if(value == "size") {
			lineStream >> x >> y;

		} // if(value == "size");

	} // while(std::getline(textfile, line));

	textfile.close();

	sizes.insert(std::make_pair(name, sf::Vector2i(x, y)));

	filename = TEABAG_SPR_IMGFILE(name);

	sf::Texture t;
	t.loadFromFile(filename);
	sheets.insert(std::make_pair(name, t));

	TEABAG_LOG("Spritesheet Loaded: " + name);

	return 0;

} // int SpriteManager::loadSpritesheet(std::string name);

sf::Texture* SpriteManager::getSpritesheet(std::string name) {
	return &(sheets.at(name));

} // sf::Texture* SpriteManager::getSpritesheet(std::string name);

sf::Vector2i SpriteManager::getSpriteSize(std::string name) {
	return sizes.at(name);

} // sf::Vector2i SpriteManager::getSpriteSize(std::string name);

TEABAG_NAMESPACE_END
