#include "inc/entity.hpp"

TEABAG_NS

Entity::Entity() {
	valid = false;

} // Entity::Entity();

Entity::Entity(sf::Sprite* e)
	: entity(e) {
	
	valid = true;

} // Entity::Entity(sf::Sprite* e);

void Entity::move(int xd, int yd) {
	if(valid) {
		entity->move(xd, yd);

	} // if(valid);

} // void Entity::move(int xd, int yd);

TEABAG_NS_END
