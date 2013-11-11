#include "inc/map.hpp"

TEABAG_NS

GameMap::GameMap() {

} // GameMap::GameMap();

int GameMap::loadMap(std::string mapname) {
	return (loadText(mapname) >= 0) && (loadImg(mapname) >= 0) && (renderTex() >= 0);

} // int GameMap::loadMap(std::string mapname);

int GameMap::loadText(std::string mapname) {
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
			bool blocking;

			if(!parser.get(r) || !parser.get(g) || !parser.get(b) || !parser.get(name) || !parser.get(blocking)) {
				TEABAG_FILE_PARSE_ERROR(filename, parser.line);
				return -1;

			} // if(!parser.get(r) || !parser.get(g) || !parser.get(name) || !parser.get(name) || !parser.get(blocking));

			if(tileManager.addTile(name, r, g, b, blocking) < 0) {
				return -1;

			} // if(tileManager.addTile(name, r, g, b, blocking) < 0);

		} // if(option == "tile");

		else if(option == "entity") {
			std::string name;
			int x, y;

			if(!parser.get(name) || !parser.get(x) || !parser.get(y)) {
				TEABAG_FILE_PARSE_ERROR(filename, parser.line);
				return -1;

			} // if(!parser.get(name) || !parser.get(x) || !parser.get(y));

			if(entityManager.addEntity(name, x, y) < 0) {
				return -1;

			} // if(entityManager.addEntity(name, x, y) < 0);

			entityNames.push_back(name);

		} // else if(option == "entity");

	} // while(parser.nextLine());

	return 0;

} // int GameMap::loadText(std::string mapname);

int GameMap::loadImg(std::string mapname) {
	std::string filename = TEABAG_MAP_IMG(mapname);

	sf::Image img;
	if(!img.loadFromFile(filename)) {
		TEABAG_IMG_ERROR(filename);
		return -1;

	} // if(!img.loadFromFile(filename));

	for(int x = 0; x < img.getSize().x; ++x) {
		tileNames.push_back(std::vector<std::string>());

		for(int y = 0; y < img.getSize().y; ++y) {
			TileInfo* t = tileManager.getTile(img.getPixel(x, y));
			tileNames.back().push_back(t ? t->name : "");

		} // for(int y = 0; y < img.getSize().y; ++y);

	} // for(int x = 0; x < img.getSize().x; ++x);

	return 0;

} // int GameMap::loadImg(std::string mapname);

int GameMap::renderTex() {
	unsigned int mapWidth = tileNames.size() * tileManager.tileWidth;
	unsigned int mapHeight = tileNames[0].size() * tileManager.tileHeight;

	if(!mapTex.create(mapWidth, mapHeight)) {
		return -1;

	} // if(!mapTex.create(mapWidth, mapHeight));

	mapTex.clear();

	for(int i = 0; i < tileNames.size(); ++i) {
		for(int j = 0; j < tileNames[0].size(); ++j) {
			sf::Sprite spr;
			spr.setTexture(tileManager.getTile(tileNames[i][j])->texture);
			spr.setPosition(i * tileManager.tileWidth, j * tileManager.tileHeight);
			mapTex.draw(spr);

		} // for(int j = 0; j < mapHeight; ++j);

	} // for(int i = 0; i < mapWidth; ++i);

	mapTex.display();
	return 0;

} // int GameMap::renderTex();


TEABAG_NS_END
