#ifndef TEABAG_EVENTMANAGER_HPP
#define TEABAG_EVENTMANAGER_HPP

#include "map.hpp"
#include "defines.hpp"
#include "entitymanager.hpp"
#include "tilemanager.hpp"

#include <cmath>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics.hpp>

TEABAG_NS

class Game;
class Entity;

struct Collision {
	std::string e1name;
	std::string e2name;
	sf::FloatRect collision;
	bool e2tile;

}; // struct Collision;

typedef std::function<void(sf::Event)> EventCallback;
typedef std::function<void()> KeyCallback;
typedef std::function<void(sf::FloatRect, sf::FloatRect, Collision)> CollisionCallback;
typedef std::function<void()> TickCallback;

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

	int addEventCallback(sf::Event::EventType eventType, teabag::EventCallback callback);
	int addKeyCallback(sf::Keyboard::Key keyCode, teabag::KeyCallback callback);
	int addCollisionCallback(std::string entityName, teabag::CollisionCallback callback);
	int addTickCallback(teabag::TickCallback callback);

	void tick(sf::RenderWindow& wind, sf::Sprite& mapSprite);

	void checkEvents(sf::RenderWindow& wind);
	void checkKeyboard();
	void checkCollision(sf::Sprite& mapSprite);

	std::unordered_map<sf::Event::EventType, std::vector<teabag::EventCallback>, std::hash<int>> eventCallbacks;
	std::unordered_map<sf::Keyboard::Key, std::vector<teabag::KeyCallback>, std::hash<int>> keyCallbacks;
	std::unordered_map<std::string, std::vector<teabag::CollisionCallback>, std::hash<std::string>> collisionCallbacks;
	std::vector<teabag::TickCallback> tickCallbacks;

	EntityManager& entityManager;
	TileManager& tileManager;
	GameMap& gameMap;

}; // class EventManager;

TEABAG_INTERNAL_END

TEABAG_NS_END

#endif // TEABAG_EVENTMANAGER_HPP
