#include "inc/tileman.hpp"

TEABAG_NAMESPACE_BEGIN

TileManager::TileManager()
	: nameFromColour(10, [](sf::Color c){ 
			std::ostringstream foo;
			foo << c.r << c.g << c.b;
			std::hash<std::string> hashFunc;
			return hashFunc(foo.str()); }) {

} // TileManager::TileManager();

int TileManager::loadTile(int r, int g, int b, std::string name, bool collision) {
	std::string filename = TEABAG_TILE_FILE(name);

	sf::Texture t;
	t.loadFromFile(filename);
	texFromName.insert(std::make_pair(name, t));

	nameFromColour.insert(std::make_pair(sf::Color(r, g, b), name));

	hasCollision.insert(std::make_pair(name, collision));

	TEABAG_LOG("Tile Loaded: " + std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b) + " " + name + " " + std::to_string(collision));

	return 0;

} // int TileManager::loadTile(int r, int g, int b, std::string name);

sf::Texture* TileManager::getTexFromColour(sf::Color colour) {
	return &(texFromName.at(nameFromColour.at(colour)));

} // sf::Texture* TileManager::getTexFromColour(sf::Color colour);

sf::Texture* TileManager::getTexFromName(std::string name) {
	return &(texFromName.at(name));

} // sf::Texture* TileManager::getTexFromName(std::string name);

std::string TileManager::getNameFromColour(sf::Color colour) {
	return nameFromColour.at(colour);

} // std::string TileManager::getNameFromColour(sf::Color colour);

bool TileManager::canCollide(std::string name) {
	return hasCollision.at(name);

} // bool TileManager::canCollide(std::string name);

TEABAG_NAMESPACE_END
