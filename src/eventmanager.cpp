#include "inc/eventmanager.hpp"

TEABAG_NS

TEABAG_INTERNAL

EventManager::EventManager(EntityManager& entityManager, TileManager& tileManager, GameMap& gameMap)
	: eventCallbacks(),
	  keyCallbacks(),
	  collisionCallbacks(),
	  tickCallbacks(),

	  entityManager(entityManager),
	  tileManager(tileManager),
	  gameMap(gameMap) {

} // EventManager::EventManager(EntityManager& entityManager, TileManager& tileManager, GameMap& gameMap);

int EventManager::addEventCallback(sf::Event::EventType eventType, teabag::EventCallback callback) {
	eventCallbacks[eventType].push_back(callback);

	return 0;

} // int EventManager::addEventCallback(sf::Event::EventType eventType, teabag::EventCallback callback);

int EventManager::addKeyCallback(sf::Keyboard::Key keyCode, teabag::KeyCallback callback) {
	keyCallbacks[keyCode].push_back(callback);

	return 0;

} // int EventManager::addKeyCallback(sf::Keyboard::Key keyCode, teabag::KeyCallback callback);

int EventManager::addCollisionCallback(std::string entityName, teabag::CollisionCallback callback) {
	collisionCallbacks[entityName].push_back(callback);

	return 0;

} // int EventManager::addCollisionCallback(std::string entityName, teabag::CollisionCallback callback);

int EventManager::addTickCallback(teabag::TickCallback callback) {
	tickCallbacks.push_back(callback);

	return 0;

} // int EventManager::addTickCallback(teabag::TickCallback callback);

void EventManager::tick(sf::RenderWindow& wind, sf::Sprite& mapSprite) {
	for(auto f : tickCallbacks) {
		f();

	} // for(auto f : tickCallbacks);

	checkEvents(wind);
	checkKeyboard();
	checkCollision(mapSprite);

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

void EventManager::checkCollision(sf::Sprite &mapSprite) {
    sf::FloatRect coll;
    bool collisionFound;
    do {
        collisionFound = false;
        for(auto p : collisionCallbacks) {
            sf::Sprite& entity = entityManager.entityMap[p.first];

            // Tile Collisions
            sf::FloatRect& entityBounds = entity.getGlobalBounds();
            int x0 = entityBounds.left / tileManager.tileWidth;
            int y0 = entityBounds.top  / tileManager.tileHeight;

            sf::FloatRect& mapBounds = mapSprite.getGlobalBounds();
            int offsetX = (entityBounds.left - mapBounds.left) / tileManager.tileWidth;
            int offsetY = (entityBounds.top  - mapBounds.top)  / tileManager.tileHeight;

            int x1 = x0 + (entityBounds.width  / tileManager.tileWidth)  + 2;
            int y1 = y0 + (entityBounds.height / tileManager.tileHeight) + 2;

            for(int x = (x0 > 0 ? x0 - 1 : 0); x < x1; x++) {
                for(int y = (y0 > 0 ? y0 - 1 : 0); y < y1; y++) {
                    int tileX = offsetX + (x - x0);
                    int tileY = offsetY + (y - y0);
                    if(tileX >= 0 && tileX < gameMap.tileNames.size()
                    && tileY >= 0 && tileY < gameMap.tileNames[0].size()) {
                        std::string tile = gameMap.tileNames[tileX][tileY];
                        if(tileManager.isBlocking(tile)) {
                            sf::FloatRect tileRect = sf::FloatRect(
                                (tileX * tileManager.tileWidth) + mapSprite.getGlobalBounds().left,
                                (tileY * tileManager.tileHeight) + mapSprite.getGlobalBounds().top,
                                tileManager.tileWidth, tileManager.tileHeight);
                            if(entityBounds.intersects(tileRect, coll)) {
                                bool c = true;
                                if(tileManager.hasCollisionMap(tile)) {
                                    c = checkDetailedCollision(
                                            entity.getGlobalBounds(),
                                            tileRect,
                                            tileManager.getCollisionMap(tile),
                                            coll);
                                }
                                if(c) {
                                    for(auto f : p.second) {
                                        f(entityBounds, tileRect, {p.first, tile, coll, true});
                                    }
                                    collisionFound = true;
                                }
                            }
                        }
                    }
                }
            }

            // Entity Collisions
            for(auto entp : entityManager.entityMap) {
                if((p.first != entp.first) && entityBounds.intersects(entp.second.getGlobalBounds(), coll)) {
                    for(auto f : p.second) {
                        f(entityBounds, entp.second.getGlobalBounds(), {p.first, entp.first, coll, false});
                    }
                    collisionFound = true;
                }
            }
        }
    } while(collisionFound);
}

bool EventManager::checkDetailedCollision(sf::FloatRect obj1, sf::FloatRect obj2, std::vector<std::vector<bool>>* obj1map, sf::FloatRect& collision) {
	int maxX = collision.left;
	int maxY = collision.top;

	int minX = collision.left + collision.width;
	int minY = collision.top + collision.height;

	bool ret = false;

	for(int x = collision.left; x < collision.left + collision.width; x++) {
		for(int y = collision.top; y < collision.top + collision.height; y++) {
			if(obj1map->operator[](x - obj2.left)[y - obj2.top]) {
				minX = std::min(minX, x);
				minY = std::min(minY, y);

				maxX = std::max(maxX, x);
				maxY = std::max(maxY, y);

				ret = true;

			} // if(obj1map->operator[](x)[y]);

		} // for(int y = collision.top; y < collision.height; y++);

	} // for(int x = collision.left; x < collision.width; x++);

	if(ret) {
		collision = sf::FloatRect(minX, minY, maxX - minX, maxY - minY); 

	} // if(ret);

	return ret;

} // bool EventManager::checkDetailedCollision(sf::FloatRect obj1, sf::FloatRect obj2, std::vector<std::vector<bool>>* obj1map, sf::FloatRect& collision);

TEABAG_INTERNAL_END

TEABAG_NS_END
