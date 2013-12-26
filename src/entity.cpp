#include "inc/entity.hpp"

TEABAG_NS

Entity::Entity() {
	valid = false;

} // Entity::Entity();

Entity::Entity(std::string name, internal::EntityManager* entMan, internal::EventManager* evtMgr)
	: name(name) {

	funcMove = std::bind(static_cast<void(sf::Sprite::*)(float, float)>(&sf::Sprite::move), entMan->getEntity(name), std::placeholders::_1, std::placeholders::_2);
	funcCollision = std::bind(&internal::EventManager::addCollisionCallback, evtMgr, std::placeholders::_1, std::placeholders::_2);
	
	valid = true;

} // Entity::Entity(std::string name, internal::EntityManager* entMan, internal::EventManager* evtMgr);

void Entity::onCollision(CollisionCallback callback) {
	if(valid) {
		funcCollision(name, callback);

	} // if(valid);

} // void Entity::onCollision(CollisionCallback callback);

void Entity::move(int xd, int yd) {
	if(valid) {
		funcMove(xd, yd);

	} // if(valid);

} // void Entity::move(int xd, int yd);

TEABAG_NS_END
