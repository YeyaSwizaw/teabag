#include "inc/collision.hpp"

TEABAG_NAMESPACE_BEGIN

Collision::Collision() {

} // Collision::Collision();

Collision::Collision(std::string obj1, std::string obj2,
		sf::FloatRect obj1Bounds, sf::FloatRect obj2Bounds,
		sf::FloatRect collisionBounds, bool hasTile)

	: obj1(obj1), obj2(obj2),
	  obj1Bounds(obj1Bounds), obj2Bounds(obj2Bounds),
	  collisionBounds(collisionBounds), hasTile(hasTile) {

} // Collision::Collision;

TEABAG_NAMESPACE_END
