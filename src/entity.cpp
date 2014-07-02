#include "inc/entity.hpp"

TEABAG_NS

Entity::Entity(std::string name, int x, int y, internal::Texture& tex)
    : name(name) {

    sprite.setPosition(x, y);
    sprite.setTexture(tex.tex);
    sprite.setTextureRect({0, 0, tex.spriteWidth, tex.spriteHeight});
} 

void Entity::move(int x, int y) {
    sprite.move(x, y);
} 

void Entity::place(int x, int y) {
    sprite.setPosition(x, y);
} 

void Entity::setSpriteCoord(int x, int y) {
    auto r = sprite.getTextureRect();
    sprite.setTextureRect({x * r.width, y * r.height, r.width, r.height});
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
