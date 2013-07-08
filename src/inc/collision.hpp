#ifndef TEABAG_COLLISION_HPP
#define TEABAG_COLLISION_HPP

#include "defines.hpp"

#include <string>

#include <SFML/Graphics.hpp>

TEABAG_NAMESPACE_BEGIN

class Collision {
public:
	Collision();

	Collision(std::string obj1, std::string obj2,
			sf::FloatRect obj1Bounds, sf::FloatRect obj2Bounds,
			sf::FloatRect collisionBounds, bool hasTile);

	std::string obj1, obj2;
	sf::FloatRect obj1Bounds, obj2Bounds, collisionBounds;
	bool hasTile;

}; // class Collision;

TEABAG_NAMESPACE_END

#endif // TEABAG_COLLISION_HPP
