#include "inc/entity.hpp"

TEABAG_NAMESPACE_BEGIN

Entity::Entity(sf::Vector2f pos, std::string sprName, sf::Vector2i sprPos)
	: sprName(sprName),
	  sprPos(sprPos) {

	sprite.setPosition(pos);

} // Entity::Entity(sf::Vector2f pos, std::string sprName, sf::Vector2i sprPos);

void Entity::move(sf::Vector2f delta) {
	sprite.move(delta);

} // void Entity::move(sf::Vector2f delta);

TEABAG_NAMESPACE_END
