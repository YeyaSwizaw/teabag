#include "inc/game.hpp"

TEABAG_NS

Game::Game() {

} // Game::Game();

int Game::init(bool loadMapNow) {
	std::string file = TEABAG_MAIN_FILE;
	OptionsParser parser(file);
	if(!parser) {
		TEABAG_FILE_OPEN_ERROR(file);
		return -1;

	} // if(!parser);

	unsigned int width = TEABAG_DEF_WIN_WIDTH;
	unsigned int height = TEABAG_DEF_WIN_HEIGHT;
	std::string name = TEABAG_DEF_NAME;
	std::string start;

	while(parser.nextLine()) {
		std::string option;
		if(!parser.get(option)) {
			TEABAG_FILE_PARSE_ERROR(file, parser.line);
			return -1;

		} // if(!parser.get(option));

		if(option == "name") {
			name = parser.line.substr(5);

		} // if(option == "name");
		else if(option == "wind") {
			if(!parser.get(width) || !parser.get(height)) {
				TEABAG_FILE_PARSE_ERROR(file, parser.line);
				return -1;

			} // if(!parser.get(width));

		} // else if(option == "wind");
		else if(option == "start") {
			if(!parser.get(start)) {
				TEABAG_FILE_PARSE_ERROR(file, parser.line);
				return -1;

			} // if(!parser.get(start));

		} // else if(option == "start");

	} // while(parser.nextLine());

	gameWind.create(sf::VideoMode(width, height), name);

	if(loadMapNow) {
		if(start.empty()) {
			return -1;

		} // if(start.empty());

		if(gameMap.loadMap(start) < 0) {
			return -1;

		} // if(gameMap.loadMap(start) < 0);

		for(auto a : gameMap.tileNames) {
			for(auto b : a) {
				std::cout << b.substr(0, 1) << ":";

			} // for(auto b : a);

			std::cout << std::endl;

		} // for(auto a : gameMap.tileNames);

	} // if(loadMapNow);

	return 0;

} // int Game::init(bool loadMapNow);

int Game::addEventCallback(sf::Event::EventType eventType, std::function<void(sf::Event)> callback) {
	return eventManager.addEventCallback(eventType, callback);

} // int Game::addEventCallback(sf::Event::EventType eventType, std::function<void(sf::Event)> callback);

int Game::run() {
	while(gameWind.isOpen()) {
		eventManager.tick(gameWind);

		gameWind.clear();
		gameWind.display();

	} // while(gameWind.isOpen());

	return 0;

} // int Game::run();

void Game::exit() {
	gameWind.close();

} // void Game::exit();

TEABAG_NS_END
