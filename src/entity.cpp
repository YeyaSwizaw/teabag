#include "inc/entity.hpp"

TEABAG_NS

Entity::Entity(int x, int y, sf::Texture& tex) {
    sprite.setPosition(x, y);
    sprite.setTexture(tex);
} 

void Entity::move(int x, int y) {
    sprite.move(x, y);
} 

TEABAG_NS_END
