#include "inc/entity.hpp"

TEABAG_NS

Entity::Entity() {
	valid = false;

} // Entity::Entity();

Entity::Entity(std::string name, internal::EntityManager* entMan, internal::EventManager* evtMgr) {

	funcMove = std::bind(static_cast<void(sf::Sprite::*)(float, float)>(&sf::Sprite::move), entMan->getEntity(name), std::placeholders::_1, std::placeholders::_2);
	funcCollision = std::bind(&internal::EventManager::addCollisionCallback, evtMgr, name, std::placeholders::_1);
	funcGetBounds = std::bind(&sf::Sprite::getGlobalBounds, entMan->getEntity(name));
	
	valid = true;

} // Entity::Entity(std::string name, internal::EntityManager* entMan, internal::EventManager* evtMgr);

void Entity::onCollision(CollisionCallback callback) {
	if(valid) {
		funcCollision(callback);

	} // if(valid);

} // void Entity::onCollision(CollisionCallback callback);

void Entity::move(int xd, int yd) {
	if(valid) {
		funcMove(xd, yd);

	} // if(valid);

} // void Entity::move(int xd, int yd);

sf::FloatRect Entity::getBounds() {
	return (valid ? funcGetBounds() : sf::FloatRect());

} // sf::FloatRect getBounds();

int Entity::getX() {
	return (valid ? funcGetBounds().left : 0);

} // int Entity::getX();

int Entity::getY() {
	return (valid ? funcGetBounds().top : 0);

} // int Entity::getY();

TEABAG_NS_END
