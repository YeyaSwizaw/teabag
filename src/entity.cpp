#include "inc/entity.hpp"

TEABAG_NS

Entity::Entity(std::string name, int x, int y, sf::Texture& tex)
    : name(name) {

    sprite.setPosition(x, y);
    sprite.setTexture(tex);
} 

void Entity::move(int x, int y) {
    sprite.move(x, y);
} 

void Entity::place(int x, int y) {
    sprite.setPosition(x, y);
} 

EntitySignals& Entity::signals() {
    return sigs;
} 

int Entity::x() const {
    return sprite.getPosition().x;
} 

int Entity::y() const {
    return sprite.getPosition().y;
} 

TEABAG_NS_END
