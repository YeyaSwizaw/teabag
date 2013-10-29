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

int EventManager::addCollisionCallback(std::string entName, std::function<void(Collision)> func) {
	if(collisionCallbacks.count(entName) == 0) {
		collisionCallbacks.insert(std::make_pair(entName, std::vector<std::function<void(Collision)>>({ func })));

	} // if(collisionCallbacks.count(entName) == 0);
	else {
		collisionCallbacks.at(entName).push_back(func);

	} // else;

	return 0;

} // int EventManager::addCollisionCallback(std::string entName, std::function<void(Collision)> func);

int EventManager::addTickCallback(std::function<void()> func) {
	tickCallbacks.push_back(func);

	return 0;

} // int EventManager::addTickCallback(std::function<void()> func);

void EventManager::handleEvent(sf::Event e) {
	if(callbacks.count(e.type) != 0) {
		for(auto& f : callbacks.at(e.type)) {
			f(e);

		} // for(auto& f : callbacks.at(e.type));

	} // if(callbacks.count(e.type) != 0);

} // void EventManager::handleEvent(sf::Event e);

void EventManager::checkCollisions(EntityManager *entMan, TileManager *tileMan, GameMap *gMap) {
	for(auto& collPair : collisionCallbacks) {
		Entity* e = entMan->getEntity(collPair.first);

		sf::FloatRect collRect;

		for(auto& entPair : entMan->entities) {
			if(collPair.first != entPair.first) {
				while(e->sprite.getGlobalBounds().intersects(entPair.second.sprite.getGlobalBounds(), collRect)) {
					for(auto& f : collPair.second) {
						f(Collision(collPair.first, entPair.first, 
									e->sprite.getGlobalBounds(), entPair.second.sprite.getGlobalBounds(),
									collRect, false));

					} // for(auto& f : collPair.second);

				} // while(e.sprite.getGlobalBounds().intersects(entPair.second.sprite.getGlobalBounds()));

			} // if(collPair.first != entPair.first);

		} // for(auto* entPair : entMan->entities);

		Collision coll;

		while([&](Collision &c) { // while(lambda)...
			int x1 = (int)std::floor(e->sprite.getGlobalBounds().left / gMap->tileSize);
			int y1 = (int)std::floor(e->sprite.getGlobalBounds().top / gMap->tileSize);

			int sprx = (int)std::ceil(e->sprite.getGlobalBounds().width / gMap->tileSize);
			int spry = (int)std::ceil(e->sprite.getGlobalBounds().height / gMap->tileSize);

			for(int x = x1; x <= (x1 + sprx) && x < gMap->mapTileNames.size(); x++) {
				for(int y = y1; y <= (y1 + spry) && y < gMap->mapTileNames[x].size(); y++) {
					if(tileMan->canCollide(gMap->mapTileNames[x][y])) {
						c.obj1 = collPair.first;
						c.obj2 = gMap->mapTileNames[x][y];
						c.obj1Bounds = e->sprite.getGlobalBounds();
						c.obj2Bounds = sf::FloatRect(x, y, gMap->tileSize, gMap->tileSize);
						c.obj1Bounds.intersects(c.obj2Bounds, c.collisionBounds);
						c.hasTile = true;

						return true;

					} // if(tileMan->canCollide(gMap->mapTileNames[y][x]));

				} // for(int y = y1; y <= (y1 + 1); y++);

			} // for(int x = x1; x <= (x1 + 1); x++);

			return false;

		}(coll)) { // ...do this
			for(auto& f : collPair.second) {
				f(coll);

			} // for(auto& f : collPair.second);

		} // });

	} // for(auto& p : collisionCallbacks);

} // void EventManager::checkCollisions(EntityManager *entMan, TileManager *tileMan, GameMap *gMap);

void EventManager::callTickCallbacks() {
	for(auto& f : tickCallbacks) {
		f();

	} // for(auto& f : tickCallbacks);

} // void EventManager::callTickCallbacks();

TEABAG_NAMESPACE_END
