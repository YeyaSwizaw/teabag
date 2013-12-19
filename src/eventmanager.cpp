#include "inc/eventmanager.hpp"

TEABAG_NS

TEABAG_INTERNAL

EventManager::EventManager()
	: eventCallbacks() {

} // EventManager::EventManager();

int EventManager::addEventCallback(sf::Event::EventType eventType, std::function<void(sf::Event)> callback) {
	eventCallbacks[eventType].push_back(callback);

	return 0;

} // int EventManager::addEventCallback(sf::Event::EventType eventType, std::function<void(sf::Event)> callback);

void EventManager::tick(sf::RenderWindow& wind) {
	sf::Event e;
	while(wind.pollEvent(e)) {
		for(auto& f : eventCallbacks[e.type]) {
			f(e);

		} // for(auto& f : eventCallbacks[e.type]);

	} // while(wind.pollEvent(e));

} // void EventManager::tick(sf::RencerWindow& wind);

TEABAG_INTERNAL_END

TEABAG_NS_END
