#ifndef TEABAG_EVENTMANAGER_HPP
#define TEABAG_EVENTMANAGER_HPP

#include "defines.hpp"

#include <unordered_map>
#include <vector>

#include <SFML/Graphics.hpp>

TEABAG_NS

class Game;

class EventManager {
private:
	friend class Game;

	EventManager();

	int addEventCallback(sf::Event::EventType eventType, std::function<void(sf::Event)> callback);

	void tick(sf::RenderWindow& wind);

	std::unordered_map<sf::Event::EventType, std::vector<std::function<void(sf::Event)>>, std::hash<int>> eventCallbacks;

}; // class EventManager;

TEABAG_NS_END

#endif // TEABAG_EVENTMANAGER_HPP
