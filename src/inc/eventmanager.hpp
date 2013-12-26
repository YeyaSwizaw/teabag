#ifndef TEABAG_EVENTMANAGER_HPP
#define TEABAG_EVENTMANAGER_HPP

#include "defines.hpp"
#include "entitymanager.hpp"
#include "tilemanager.hpp"

#include <unordered_map>
#include <vector>

#include <SFML/Graphics.hpp>

TEABAG_NS

class Game;
class Entity;

TEABAG_INTERNAL

/**
 * Manages events.
 * This class is used internally to manage events and callback functions.
 */
class EventManager {
private:
	friend class teabag::Game;
	friend class teabag::Entity;

	EventManager(EntityManager& entityManager, TileManager& tileManager, GameMap& gameMap);

	int addEventCallback(sf::Event::EventType eventType, std::function<void(sf::Event)> callback);
	int addKeyCallback(sf::Keyboard::Key keyCode, std::function<void()> callback);
	int addCollisionCallback(std::string entityName, std::function<void(sf::FloatRect, sf::FloatRect, sf::FloatRect)> callback);

	void tick(sf::RenderWindow& wind);

	void checkEvents(sf::RenderWindow& wind);
	void checkKeyboard();
	void checkCollision();

	std::unordered_map<sf::Event::EventType, std::vector<std::function<void(sf::Event)>>, std::hash<int>> eventCallbacks;
	std::unordered_map<sf::Keyboard::Key, std::vector<std::function<void()>>, std::hash<int>> keyCallbacks;
	std::unordered_map<std::string, std::vector<std::function<void(sf::FloatRect, sf::FloatRect, sf::FloatRect)>>, std::hash<std::string>> collisionCallbacks;

	EntityManager& entityManager;
	TileManager& tileManager;
	GameMap& gameMap;

}; // class EventManager;

TEABAG_INTERNAL_END

TEABAG_NS_END

#endif // TEABAG_EVENTMANAGER_HPP
