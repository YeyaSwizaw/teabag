#include "inc/eventmanager.hpp"

TEABAG_NS

TEABAG_INTERNAL

EventManager::EventManager(EntityManager& entityManager, TileManager& tileManager, GameMap& gameMap)
	: eventCallbacks(),
	  keyCallbacks(),
	  collisionCallbacks(),

	  entityManager(entityManager),
	  tileManager(tileManager),
	  gameMap(gameMap) {

} // EventManager::EventManager(EntityManager& entityManager, TileManager& tileManager, GameMap& gameMap);

int EventManager::addEventCallback(sf::Event::EventType eventType, std::function<void(sf::Event)> callback) {
	eventCallbacks[eventType].push_back(callback);

	return 0;

} // int EventManager::addEventCallback(sf::Event::EventType eventType, std::function<void(sf::Event)> callback);

int EventManager::addKeyCallback(sf::Keyboard::Key keyCode, std::function<void()> callback) {
	keyCallbacks[keyCode].push_back(callback);

	return 0;

} // int EventManager::addKeyCallback(sf::Keyboard::Key keyCode, std::function<void()> callback);

int EventManager::addCollisionCallback(std::string entityName, std::function<void(sf::FloatRect, sf::FloatRect, sf::FloatRect)> callback) {
	collisionCallbacks[entityName].push_back(callback);

	return 0;

} // int EventManager::addCollisionCallback(std::string entityName, std::function<void(sf::FloatRect, sf::FloatRect, sf::FloatRect)> callback);

void EventManager::tick(sf::RenderWindow& wind) {
	checkEvents(wind);
	checkKeyboard();
	checkCollision();

} // void EventManager::tick(sf::RenderWindow& wind);

void EventManager::checkEvents(sf::RenderWindow& wind) {
	sf::Event e;
	while(wind.pollEvent(e)) {
		for(auto& f : eventCallbacks[e.type]) {
			f(e);

		} // for(auto& f : eventCallbacks[e.type]);

	} // while(wind.pollEvent(e));

} // void EventManager::checkEvents(sf::RenderWindow& wind);

void EventManager::checkKeyboard() {
	for(auto p : keyCallbacks) {
		if(sf::Keyboard::isKeyPressed(p.first)) {
			for(auto f : p.second) {
				f();

			} // for(auto f : p.second);

		} // if(sf::Keyboard::isKeyPressed(p.first));

	} // for(auto p : keyCallbacks);

} // void EventManager::checkKeyboard();

void EventManager::checkCollision() {
	sf::FloatRect coll;
	bool collisionFound = false;

	do {
		collisionFound = false;

		for(auto p : collisionCallbacks) {
			sf::Sprite& entity = entityManager.entityMap[p.first];

			for(auto entp : entityManager.entityMap) {
				if((p.first != entp.first) && entity.getGlobalBounds().intersects(entp.second.getGlobalBounds(), coll)) {
					for(auto f : p.second) {
						f(entity.getGlobalBounds(), entp.second.getGlobalBounds(), coll);

					} // for(auto f : p.second);

					collisionFound = true;

				} // if((p.first != entp.first) && entity.getGlobalBounds().intersects(entp.second.getGlobalBounds(), coll));

			} // for(auto entp : entityManager.entityMap);

		} // for(auto p : collisionCallbacks);

	} while(collisionFound);

} // void EventManager::checkCollision(EntityManager& entman);

TEABAG_INTERNAL_END

TEABAG_NS_END
