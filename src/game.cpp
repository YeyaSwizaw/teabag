#include "inc/game.hpp"

TEABAG_NAMESPACE_BEGIN

Game::Game()
	: tileMan(),
	  sprMan(),
	  entMan(),
	  gameMap(&tileMan, &sprMan, &entMan) {

} // Game::Game(bool init);

int Game::init(bool loadMapNow) {
	TEABAG_LOG("Reading main game definition file.")

	std::ifstream mainfile(TEABAG_MAIN_FILE, std::ifstream::in);
	if(!mainfile) {
		TEABAG_FILE_NOT_FOUND(TEABAG_MAIN_FILE)
		return -1;

	} // if(!mainfile);

	unsigned int winWidth = TEABAG_DEFAULT_WIN_WIDTH;
	unsigned int winHeight = TEABAG_DEFAULT_WIN_HEIGHT;

	unsigned int fpsLimit = TEABAG_DEFAULT_FRAMERATE_LIMIT;

	std::string line;
	while(std::getline(mainfile, line)) {
		std::istringstream lineStream(line);
		std::string value;

		lineStream >> value;

		if(value == "name") {
			gameName = lineStream.str().substr(5);

		} // if(value == "name");

		else if(value == "windowsize") {
			lineStream >> winWidth >> winHeight;

		} // else if(value == "windowsize");

		else if(value == "fps") {
			lineStream >> fpsLimit;

		} // else if(value == "fps");
		
		else if(value == "start") {
			lineStream >> gameMap.mapName;

		} // else if(value == "start");

	} // while(std::getline(mainfile, line));

	mainfile.close();

	if(gameName.empty()) {
		TEABAG_LOG("No game name provided.")
		gameName = TEABAG_DEFAULT_NAME;

	} // if(gameName == "");

	TEABAG_LOG("Game name: " + gameName)

	if(loadMapNow) {
		if(gameMap.mapName.empty()) {
			TEABAG_ERROR("No initial map set to load.")
			return -1;

		} // if(currentMapName.empty());
		else {
			if(gameMap.loadMap() < 0) {
				return -1;

			} // if(loadMap() < 0);

		} // else;

	} // if(loadMapNow);

	TEABAG_LOG("Opening SFML window.")
	gameWindow.create(sf::VideoMode(winWidth, winHeight), gameName);

	gameWindow.setFramerateLimit(fpsLimit);

	return 0;

} // void Game::init();

int Game::addEventCallback(sf::Event::EventType sfEventType, std::function<void(sf::Event)> func) {
	return eventMan.addCallback(sfEventType, func);

} // int Game::addEventCallback(sf::Event::EventType sfEventType, std::function<void(sf::Event)> func);

int Game::addCollisionCallback(std::string entName, std::function<void(std::string, bool)> func) {
	return eventMan.addCollisionCallback(entName, func);

} // int Game::addCollisionCallback(std::string entName, std::function<void(std::string, bool)> func);

int Game::addTickCallback(std::function<void()> func) {
	return eventMan.addTickCallback(func);

} // int Game::addTickCallback(std::function<void()> func);

bool Game::isKeyDown(sf::Keyboard::Key k) {
	return sf::Keyboard::isKeyPressed(k);

} // bool Game::isKeyDown(sf::Keyboard::Key k);

Entity* Game::getEntity(std::string name) {
	return entMan.getEntity(name);

} // Entity* Game::getEntity(std::string name);

int Game::run() {
	while(gameWindow.isOpen()) {
		eventMan.callTickCallbacks();

		sf::Event e;
		while(gameWindow.pollEvent(e)) {
			eventMan.handleEvent(e);

		} // while(gameWindow.pollEvent(e));

		eventMan.checkCollisions(&entMan, &tileMan, &gameMap);

		gameWindow.clear();

		for(auto& v : gameMap.mapTiles) {
			for(auto& t : v) {
				gameWindow.draw(t);

			} // for(auto& t : v);

		} // for(auto& v : gameMap.mapTiles);

		for(auto& p : entMan.entities) {
			gameWindow.draw(p.second.sprite);

		} // for(auto& p : entMan.entities);

		gameWindow.display();

	} // while(gameWindow.isOpen());

	return 0;

} // int Game::run();

int Game::quit() {
	gameWindow.close();

	return 0;

} // int Game::quit();

TEABAG_NAMESPACE_END
