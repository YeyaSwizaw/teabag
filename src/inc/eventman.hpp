#ifndef TEABAG_EVENTMAN_HPP
#define TEABAG_EVENTMAN_HPP

#include "defines.hpp"
#include "entity.hpp"
#include "entman.hpp"
#include "tileman.hpp"
#include "map.hpp"

#include <functional>
#include <unordered_map>
#include <vector>

#include <SFML/Window.hpp>

TEABAG_NAMESPACE_BEGIN

class EventManager {
public:
	EventManager();

	int addCallback(sf::Event::EventType sfEventType, std::function<void(sf::Event)> func);
	int addCollisionCallback(std::string entName, std::function<void(std::string, bool)> func);
	int addTickCallback(std::function<void()> func);

	void handleEvent(sf::Event e);
	void checkCollisions(EntityManager *entMan, TileManager *tileMan, GameMap *gMap);
	void callTickCallbacks();

private:
	std::unordered_map<int, std::vector<std::function<void(sf::Event)>>> callbacks;
	std::unordered_map<std::string, std::vector<std::function<void(std::string, bool)>>> collisionCallbacks;
	std::vector<std::function<void()>> tickCallbacks;

}; // class EventManager;

TEABAG_NAMESPACE_END

#endif // TEABAG_EVENTMAN_HPP
