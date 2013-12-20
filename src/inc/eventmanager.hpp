#ifndef TEABAG_EVENTMANAGER_HPP
#define TEABAG_EVENTMANAGER_HPP

#include "defines.hpp"
#include "entitymanager.hpp"

#include <unordered_map>
#include <vector>

#include <SFML/Graphics.hpp>

TEABAG_NS

class Game;

TEABAG_INTERNAL

/**
 * Manages events.
 * This class is used internally to manage events and callback functions.
 */
class EventManager {
private:
	friend class teabag::Game;

	EventManager();

	int addEventCallback(sf::Event::EventType eventType, std::function<void(sf::Event)> callback);
	int addKeyCallback(sf::Keyboard::Key keyCode, std::function<void()> callback);
	int addCollisionCallback(std::string entityName, std::function<void(sf::FloatRect, sf::FloatRect, sf::FloatRect)> callback);

	void tick(sf::RenderWindow& wind, EntityManager& entman);

	void checkEvents(sf::RenderWindow& wind);
	void checkKeyboard();
	void checkCollision(EntityManager& entman);

	std::unordered_map<sf::Event::EventType, std::vector<std::function<void(sf::Event)>>, std::hash<int>> eventCallbacks;
	std::unordered_map<sf::Keyboard::Key, std::vector<std::function<void()>>, std::hash<int>> keyCallbacks;
	std::unordered_map<std::string, std::vector<std::function<void(sf::FloatRect, sf::FloatRect, sf::FloatRect)>>, std::hash<std::string>> collisionCallbacks;

}; // class EventManager;

TEABAG_INTERNAL_END

TEABAG_NS_END

#endif // TEABAG_EVENTMANAGER_HPP
