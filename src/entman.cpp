#include "inc/entman.hpp"

TEABAG_NAMESPACE_BEGIN

EntityManager::EntityManager() {

} // EntityManager::EntityManager();

int EntityManager::loadEntity(int x, int y, std::string name) {
	std::string filename = TEABAG_ENT_FILE(name);

	std::ifstream textfile(filename);

	if(!textfile) {
		TEABAG_FILE_NOT_FOUND(filename)
		return -1;

	} // if(!textfile);

	std::string sprName;
	int sprx, spry;

	std::string line;
	while(std::getline(textfile, line)) {
		std::istringstream lineStream(line);
		std::string value;

		lineStream >> value;

		if(value == "spritesheet") {
			lineStream >> sprName >> sprx >> spry;

		} // if(value == "spritesheet");

	} // while(std::string getline(textfile, line));

	textfile.close();

	entities.insert(std::make_pair(name, Entity(sf::Vector2f(x, y), sprName, sf::Vector2i(sprx, spry))));

	TEABAG_LOG("Entity loaded: " + std::to_string(x) + " " + std::to_string(y) + " " + name);

	return 0;

} // int EntityManager::loadEntity(int x, int y, std::string name);

int EntityManager::setAllSprites(SpriteManager *sprMan) {
	for(auto& p : entities) {
		int sprX = p.second.sprPos.x;
		int sprY = p.second.sprPos.y;
		int sprWidth = sprMan->getSpriteSize(p.second.sprName).x;
		int sprHeight = sprMan->getSpriteSize(p.second.sprName).y;

		p.second.sprite.setTexture(*(sprMan->getSpritesheet(p.second.sprName)));
		p.second.sprite.setTextureRect(sf::IntRect(sprX * sprWidth, sprY * sprHeight, sprWidth, sprHeight));

	} // for(auto& p : entities);

	return 0;

} // int EntityManager::setAllSprites(SpriteManager *sprMan);

Entity* EntityManager::getEntity(std::string name) {
	return (entities.count(name) == 0 ? NULL : &(entities.at(name)));

} // Entity* EntityManager::getEntity(std::string name);

TEABAG_NAMESPACE_END
