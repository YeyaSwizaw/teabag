#include "inc/tilemanager.hpp"

TEABAG_NS

TEABAG_INTERNAL

TileManager::TileManager()
	: tileWidth(0), tileHeight(0), colourMap(10, [](sf::Color c) {
		return std::hash<std::string>()(static_cast<std::ostringstream&>(std::ostringstream().flush() << c.r << c.g << c.b).str());
									}) {

} // TileManager::TileManager();

TileManager::~TileManager() {
	clear();

} // TileManager::~TileManager();

int TileManager::addTile(std::string name, int r, int g, int b, bool blocking, bool hasMap) {
	std::string filename = TEABAG_TILE_IMG(name);

	sf::Texture tex;
	if(!tex.loadFromFile(filename)) {
		TEABAG_IMG_ERROR(filename);
		return -1;

	} // if(!t.loadFromFile(filename));

	if(colourMap.empty()) {
		tileWidth = tex.getSize().x;
		tileHeight = tex.getSize().y;

	} // if(colourMap.empty());

	TileInfo* t = new TileInfo;
	t->name = name;
	t->colour = sf::Color(r, g, b);
	t->blocking = blocking;
	t->texture = tex;

	if(hasMap) {
		filename = TEABAG_TILE_COLL_IMG(name);

		sf::Image collImg;
		if(!collImg.loadFromFile(filename)) {
			TEABAG_IMG_ERROR(filename);
			return -1;

		} // if(!collImg.loadFromFile(filename));

		t->collisionMap = new std::vector<std::vector<bool>>();
		for(int i = 0; i < tileWidth; i++) {
			t->collisionMap->push_back(std::vector<bool>());

			for(int j = 0; j < tileHeight; j++) {
				t->collisionMap->operator[](i).push_back(collImg.getPixel(i, j) != sf::Color::White);

			} // for(int j = 0; j < tileHeight; j++);

		} // for(int i = 0; i < tileWidth; i++);

	} // if(hasMap);
	else {
		t->collisionMap = nullptr;

	} // else;

	colourMap.insert({t->colour, t});
	nameMap.insert({t->name, t});

	return 0;

} // int TileManager::addTile(std::string name, int r, int g, int b, bool blocking, bool hasMap);

TileInfo* TileManager::getTile(sf::Color c) {
	return colourMap[c];

} // TileInfo* TileManager::getTile(sf::Color c);

TileInfo* TileManager::getTile(std::string name) {
	return nameMap[name];

} // TileInfo* TileManager::getTile(std::string name);

bool TileManager::isBlocking(std::string name) {
	return (nameMap[name] == nullptr ? false : nameMap[name]->blocking);

} // bool TileManager::isBlocking(std::string name);

bool TileManager::hasCollisionMap(std::string name) {
	return (nameMap[name] == nullptr ? false : nameMap[name]->collisionMap != nullptr);

} // bool TileManager::hasCollisionMap(std::string name);

std::vector<std::vector<bool>>* TileManager::getCollisionMap(std::string name) {
	return (hasCollisionMap(name) ? nameMap[name]->collisionMap : nullptr);

} // std::vector<std::vector<bool>>* TileManager::getCollisionMap(std::string name);

void TileManager::clear() {
	for(auto& p : colourMap) {
		delete p.second;

	} // for(auto& p : colourMap);

	colourMap.clear();
	nameMap.clear();

} // void TileManager::clear();

TEABAG_INTERNAL_END

TEABAG_NS_END
