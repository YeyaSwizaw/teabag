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

void EventManager::handleEvent(sf::Event e) {
	if(callbacks.count(e.type) != 0) {
		for(auto& f : callbacks.at(e.type)) {
			f(e);

		} // for(auto& f : callbacks.at(e.type));

	} // if(callbacks.count(e.type) != 0);

} // void EventManager::handleEvent(sf::Event e);

TEABAG_NAMESPACE_END
