#include "inc/eventman.hpp"

TEABAG_NAMESPACE_BEGIN

EventManager::EventManager() {

} // EventManager::EventManager();

int EventManager::addCallback(sf::Event::EventType sfEventType, std::function<void(sf::Event)> func) {
	if(callbacks.count(sfEventType) == 0) {
		callbacks.insert(std::make_pair(sfEventType, std::vector<std::function<void(sf::Event)>>({ func })));

	} // if(callbacks.count(sfEventType) == 0);
	else {
		callbacks.at(sfEventType).push_back(func);

	} // else;

	return 0;

} // int EventManager::addCallback(sf::Event::EventType sfEventType, std::function<void(sf::Event)> func);

int EventManager::addCollisionCallback(std::string entName, std::function<void(std::string)> func) {
	if(collisionCallbacks.count(entName) == 0) {
		collisionCallbacks.insert(std::make_pair(entName, std::vector<std::function<void(std::string)>>({ func })));

	} // if(collisionCallbacks.count(entName) == 0);
	else {
		collisionCallbacks.at(entName).push_back(func);

	} // else;

	return 0;

} // int EventManager::addCollisionCallback(std::string entName, std::function<void(std::string)> func);

void EventManager::handleEvent(sf::Event e) {
	if(callbacks.count(e.type) != 0) {
		for(auto& f : callbacks.at(e.type)) {
			f(e);

		} // for(auto& f : callbacks.at(e.type));

	} // if(callbacks.count(e.type) != 0);

} // void EventManager::handleEvent(sf::Event e);

void EventManager::checkCollisions(EntityManager *entMan) {
	for(auto& collPair : collisionCallbacks) {
		Entity* e = entMan->getEntity(collPair.first);

		for(auto& entPair : entMan->entities) {
			if(collPair.first != entPair.first) {
				while(e->sprite.getGlobalBounds().intersects(entPair.second.sprite.getGlobalBounds())) {
					for(auto& f : collPair.second) {
						f(entPair.first);

					} // for(auto& f : collPair.second);

				} // while(e.sprite.getGlobalBounds().intersects(entPair.second.sprite.getGlobalBounds()));

			} // if(collPair.first != entPair.first);

		} // for(auto* entPair : entMan->entities);

	} // for(auto& p : collisionCallbacks);

} // void EventManager::checkCollisions(EntityManager *entMan);

TEABAG_NAMESPACE_END
