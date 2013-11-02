#include "inc/tilemanager.hpp"

TEABAG_NS

TileManager::TileManager()
	: colourMap(10, [](sf::Color c) {
		return std::hash<std::string>()(static_cast<std::ostringstream&>(std::ostringstream().flush() << c.r << c.g << c.b).str());
									}) {

} // TileManager::TileManager();

TileManager::~TileManager() {
	clear();

} // TileManager::~TileManager();

int TileManager::addTile(std::string name, int r, int g, int b, bool blocking) {
	std::string filename = TEABAG_TILE_IMG(name);

	sf::Texture tex;
	if(!tex.loadFromFile(filename)) {
		TEABAG_IMG_ERROR(filename);
		return -1;

	} // if(!t.loadFromFile(filename));

	TileInfo* t = new TileInfo;
	t->name = name;
	t->colour = sf::Color(r, g, b);
	t->blocking = blocking;
	t->texture = tex;

	colourMap.insert({t->colour, t});
	nameMap.insert({t->name, t});

	return 0;

} // int TileManager::addTile(std::string name, int r, int g, int b, bool blocking);

TileInfo* TileManager::getTile(sf::Color c) {
	return colourMap[c];

} // TileInfo* TileManager::getTile(sf::Color c);

TileInfo* TileManager::getTile(std::string name) {
	return nameMap[name];

} // TileInfo* TileManager::getTile(std::string name);

void TileManager::clear() {
	for(auto& p : colourMap) {
		delete p.second;

	} // for(auto& p : colourMap);

	colourMap.clear();
	nameMap.clear();

} // void TileManager::clear();

TEABAG_NS_END
