#ifndef TEABAG_EVENTMAN_HPP
#define TEABAG_EVENTMAN_HPP

#include "defines.hpp"

#include <functional>
#include <unordered_map>
#include <vector>

#include <SFML/Window.hpp>

TEABAG_NAMESPACE_BEGIN

class EventManager {
public:
	EventManager();

	int addCallback(sf::Event::EventType sfEventType, std::function<void(sf::Event)> func);

	void handleEvent(sf::Event e);

private:
	std::unordered_map<int, std::vector<std::function<void(sf::Event)>>> callbacks;

}; // class EventManager;

TEABAG_NAMESPACE_END

#endif // TEABAG_EVENTMAN_HPP
