#include "inc/game.hpp"

TEABAG_NS

Game::Game()
	: tileManager(),
	  entityManager(),
	  gameMap(tileManager, entityManager),
	  eventManager(entityManager, tileManager, gameMap) {

} // Game::Game();

int Game::init(bool loadMapNow) {
	std::string file = TEABAG_MAIN_FILE;
	internal::OptionsParser parser(file);
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

	// FIX
	gameWind.setFramerateLimit(60);

	if(loadMapNow) {
		if(start.empty()) {
			return -1;

		} // if(start.empty());

		if(loadMap(start) < 0) {
			return -1;

		} // if(loadMap(start) < 0);

	} // if(loadMapNow);

	return 0;

} // int Game::Game::init(bool loadMapNow);

int Game::loadMap(std::string mapname) {
	if(gameMap.loadMap(mapname) < 0) {
		return -1;

	} // if(gameMap.loadMap(start) < 0);

	mapSprite.setTexture(gameMap.mapTex.getTexture());
	mapSprite.setPosition(0, 0);

	return 0;

} // int Game::Game::loadMap(std::string mapname);

int Game::run() {
	while(gameWind.isOpen()) {
		eventManager.tick(gameWind, mapSprite);

		gameWind.clear();
		gameWind.draw(mapSprite);

		for(auto n : gameMap.entityNames) {
			gameWind.draw(entityManager.entityMap[n]);

		} // for(auto n : gameMap.entityNames);

		gameWind.display();

	} // while(gameWind.isOpen());

	return 0;

} // int Game::Game::run();

void Game::scrollMap(int xd, int yd) {
	mapSprite.move(xd, yd);

} // void Game::scrollMap(int xd, int yd);

Entity Game::getEntity(std::string name) {
	return Entity(name, &entityManager, &eventManager);

} // Entity Game::getEntity(std::string name);

void Game::exit() {
	gameWind.close();

} // void Game::exit();

// Event Functions

int Game::addEventCallback(sf::Event::EventType eventType, EventCallback callback) {
	return eventManager.addEventCallback(eventType, callback);

} // int Game::addEventCallback(sf::Event::EventType eventType, EventCallback callback);

int Game::onClose(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::Closed, callback);

} // int Game::onClose(EventCallback callback);

int Game::onResize(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::Resized, callback);

} // int Game::onResize(EventCallback callback);

int Game::onFocusLoss(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::LostFocus, callback);

} // int Game::onFocusLoss(EventCallback callback);

int Game::onFocusGain(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::GainedFocus, callback);

} // int Game::onFocusGain(EventCallback callback);

int Game::onTextEntry(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::TextEntered, callback);

} // int Game::onTextEntry(EventCallback callback);

int Game::onKeyPress(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::KeyPressed, callback);

} // int Game::onKeyPress(EventCallback callback);

int Game::onKeyRelease(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::KeyReleased, callback);

} // int Game::onKeyRelease(EventCallback callback);

int Game::onMouseWheelMove(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::MouseWheelMoved, callback);

} // int Game::onMouseWheelMove(EventCallback callback);

int Game::onMouseButtonPress(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::MouseButtonPressed, callback);

} // int Game::onMouseButtonPress(EventCallback callback);

int Game::onMouseButtonRelease(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::MouseButtonReleased, callback);

} // int Game::onMouseButtonRelease(EventCallback callback);

int Game::onMouseMove(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::MouseMoved, callback);

} // int Game::onMouseMove(EventCallback callback);

int Game::onMouseEntry(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::MouseEntered, callback);

} // int Game::onMouseEntry(EventCallback callback);

int Game::onMouseLeave(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::MouseLeft, callback);

} // int Game::onMouseLeave(EventCallback callback);

int Game::onJoystickButtonPress(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::JoystickButtonPressed, callback);

} // int Game::onJoystickButtonPress(EventCallback callback);

int Game::onJoystickButtonRelease(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::JoystickButtonReleased, callback);

} // int Game::onJoystickButtonRelease(EventCallback callback);

int Game::onJoystickMove(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::JoystickMoved, callback);

} // int Game::onJoystickMove(EventCallback callback);

int Game::onJoystickConnection(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::JoystickConnected, callback);

} // int Game::onJoystickConnection(EventCallback callback);

int Game::onJoystickDisconnection(EventCallback callback) {
	return eventManager.addEventCallback(sf::Event::JoystickDisconnected, callback);

} // int Game::onJoystickDisconnection(EventCallback callback);

int Game::onKey(sf::Keyboard::Key keyCode, KeyCallback callback) {
	return eventManager.addKeyCallback(keyCode, callback);

} // int Game::onKey(sf::Keyboard::Key keyCode, KeyCallback callback);

int Game::onCollision(std::string entityName, CollisionCallback callback) {
	return eventManager.addCollisionCallback(entityName, callback);

} // int Game::onCollision(std::string entityName, CollisionCallback callback);

int Game::onTick(TickCallback callback) {
	return eventManager.addTickCallback(callback);

} // int Game::onTick(TickCallback callback);

TEABAG_NS_END
