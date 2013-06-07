#include "inc/game.hpp"

TEABAG_NAMESPACE_BEGIN

Game::Game() {

} // Game::Game(bool init);

int Game::init(bool loadMapNow) {
	TEABAG_LOG("Reading main game definition file.")

	std::ifstream mainfile(TEABAG_MAIN_FILE, std::ifstream::in);
	if(!mainfile) {
		TEABAG_FILE_NOT_FOUND(TEABAG_MAIN_FILE)
		return -1;

	} // if(!mainfile);

	std::string line;
	while(std::getline(mainfile, line)) {
		std::istringstream lineStream(line);
		std::string value;

		lineStream >> value;

		if(value == "name") {
			gameName == lineStream.str();

		} // if(value == "name");
		else if(value == "start") {
			lineStream >> currentMapName;

		} // else if(value == "start");

	} // while(std::getline(mainfile, line));

	mainfile.close();

	if(gameName.empty()) {
		TEABAG_LOG("No game name provided.")
		gameName = TEABAG_DEFAULT_NAME;

	} // if(gameName == "");

	TEABAG_LOG("Game name: " + gameName)

	if(loadMapNow) {
		if(currentMapName.empty()) {
			TEABAG_ERROR("No initial map set to load.")
			return -1;

		} // if(currentMapName.empty());
		else {
			if(loadMap() < 0) {
				return -1;

			} // if(loadMap() < 0);

		} // else;

	} // if(loadMapNow);

	TEABAG_LOG("Opening SFML window.")
	gameWindow.create(sf::VideoMode(800, 600), gameName);

	return 0;

} // void Game::init();

int Game::loadMap(std::string mapName) {
	currentMapName = mapName;
	return loadMap();

} // int Game::loadMap(std::string mapName);

int Game::loadMap() {
	TEABAG_LOG("Loading map: " + currentMapName)

	std::string filename = TEABAG_MAP_TEXTFILE(currentMapName);
	std::ifstream mapfile(filename, std::ifstream::in);
	if(!mapfile) {
		TEABAG_FILE_NOT_FOUND(filename)
		return -1;

	} // if(!mapfile);

	// Read text file
	std::string line;
	while(std::getline(mapfile, line)) {
		std::istringstream lineStream(line);
		std::string value;

		lineStream >> value;

		if(value == "tile") {
			int r, g, b;
			std::string name;
			lineStream >> r >> g >> b >> name;

			if(tileMan.loadTile(r, g, b, name) < 0) {
				mapfile.close();
				return -1;

			} // if(loadTile(r, g, b, name) < 0);

		} // if(value == "tile");

	} // while(std::getline(mapfile, line));

	// Read image file
	filename = TEABAG_MAP_IMGFILE(currentMapName);

	sf::Image mapimg;
	if(!mapimg.loadFromFile(filename)) {
		TEABAG_FILE_NOT_FOUND(filename)
		return -1;

	} // if(!mapimg.loadFromFile(filename));

	for(int x = 0; x < mapimg.getSize().x; x++) {
		currentMapTiles.push_back(std::vector<sf::RectangleShape>());

		for(int y = 0; y < mapimg.getSize().y; y++) {
			currentMapTiles.back().push_back(sf::RectangleShape());
			currentMapTiles.back().back().setSize(sf::Vector2f(TEABAG_DEFAULT_TILE_SIZE, TEABAG_DEFAULT_TILE_SIZE));
			currentMapTiles.back().back().setPosition(x * TEABAG_DEFAULT_TILE_SIZE, y * TEABAG_DEFAULT_TILE_SIZE);
			currentMapTiles.back().back().setTexture(tileMan.getTexFromColour(mapimg.getPixel(x, y)));

		} // for(int y = 0; y < mapimg.getSize().y; y++);

	} // for(int x = 0; x < mapimg.getSize().x; x++);

	mapfile.close();

	return 0;

} // int Game::loadMap();

int Game::run() {
	while(gameWindow.isOpen()) {
		sf::Event e;
		while(gameWindow.pollEvent(e)) {
			switch(e.type) {
				case sf::Event::Closed:
					gameWindow.close();
					break;

				default:
					break;

			} // switch(e.type);

		} // while(gameWindow.pollEvent(e));

		gameWindow.clear();

		for(auto v : currentMapTiles) {
			for(auto t : v) {
				gameWindow.draw(t);

			} // for(auto t : v);

		} // for(auto v : currentMapTiles);

		gameWindow.display();

	} // while(gameWindow.isOpen());

	return 0;

} // int Game::run();

TEABAG_NAMESPACE_END
