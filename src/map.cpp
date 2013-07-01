#include "inc/map.hpp"

TEABAG_NAMESPACE_BEGIN

GameMap::GameMap(TileManager *tileMan, SpriteManager *sprMan, EntityManager *entMan)
	: tileMan(tileMan),
	  sprMan(sprMan),
	  entMan(entMan) {

} // GameMap::GameMap(TileManager *tileMan, SpriteManager *sprMan, EntityManager *entMan);

int GameMap::loadMap(std::string name) {
	mapName = name;
	return loadMap();

} // int GameMap::loadMap(std::string name);

int GameMap::loadMap() {
	TEABAG_LOG("Loading map: " + mapName)

	std::string filename = TEABAG_MAP_TEXTFILE(mapName);
	std::ifstream mapfile(filename, std::ifstream::in);

	if(!mapfile) {
		TEABAG_FILE_NOT_FOUND(filename)
		return -1;

	} // if(!mapfile);

	std::string line;
	while(std::getline(mapfile, line)) {
		std::istringstream lineStream(line);
		std::string value;

		lineStream >> value;

		if(value == "tile") {
			int r, g, b;
			std::string name;
			lineStream >> r >> g >> b >> name;

			if(tileMan->loadTile(r, g, b, name) < 0) {
				mapfile.close();
				return -1;

			} // if(tileMan->loadTile(r, g, b, name) < 0);

		} // if(value == "tile");

		if(value == "spritesheet") {
			std::string name;
			lineStream >> name;

			if(sprMan->loadSpritesheet(name) < 0) {
				mapfile.close();
				return -1;

			} // if(sprMan->loadSpritesheet(name) < 0);

		} // if(value == "spritesheet");

		if(value == "entity") {
			std::string name;
			int x, y;
			lineStream >> name >> x >> y;

			if(entMan->loadEntity(x, y, name) < 0) {
				mapfile.close();
				return -1;

			} // if(entMan->loadEntity(x, y, name) < 0);

		} // if(value == "entity");

	} // while(std::getline(mapfile, line));

	mapfile.close();

	// Read map img.
	filename = TEABAG_MAP_IMGFILE(mapName);

	sf::Image mapimg;
	if(!mapimg.loadFromFile(filename)) {
		TEABAG_FILE_NOT_FOUND(filename)
		return -1;

	} // if(!mapimg.loadFromFile(filename));

	for(int x = 0; x < mapimg.getSize().x; x++) {
		mapTiles.push_back(std::vector<sf::RectangleShape>());

		for(int y = 0; y < mapimg.getSize().y; y++) {
			mapTiles.back().push_back(sf::RectangleShape());
			mapTiles.back().back().setSize(sf::Vector2f(TEABAG_DEFAULT_TILE_SIZE, TEABAG_DEFAULT_TILE_SIZE));
			mapTiles.back().back().setPosition(x * TEABAG_DEFAULT_TILE_SIZE, y * TEABAG_DEFAULT_TILE_SIZE);
			mapTiles.back().back().setTexture(tileMan->getTexFromColour(mapimg.getPixel(x, y)));

		} // for(int y = 0; y < mapimg.getSize().y; y++);

	} // for(int x = 0; x < mapimg.getSize().x; x++);

	entMan->setAllSprites(sprMan);

	return 0;

} // int GameMap::loadMap();

TEABAG_NAMESPACE_END
