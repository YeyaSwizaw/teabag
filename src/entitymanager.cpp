#include "inc/entitymanager.hpp"

TEABAG_NS

TEABAG_INTERNAL

EntityManager::EntityManager() {}

void EntityManager::queueEntity(std::string name, int x, int y) {
    entityQueue.push_back({name, x, y});
} 

void EntityManager::loadQueue() {
    entities.clear();
    textures.clear();

    for(EntityInfo& entity : entityQueue) {
        loadEntity(entity);
    } 

    entityQueue.clear();
} 

void EntityManager::loadEntity(EntityInfo& entity) {
    std::string file = TEABAG_ENTITY_TEA(entity.name);

    internal::Reader reader(file);
    if(!reader) {
        throw FileOpenError(file);
    } 

    std::string sprite;

    while(reader.nextLine()) {
        std::string option;
        if(!reader.get(option)) {
            throw LineReadError(file, reader.line);
        } 

        if(option == "sprite") {
            if(!reader.get(sprite)) {
                throw LineReadError(file, reader.line);
            } 
        } 
    } 

    if(textures.find(sprite) == textures.end()) {
        file = TEABAG_SPRITE_IMG(sprite);

        sf::Texture tex;
        if(!tex.loadFromFile(file)) {
            throw FileOpenError(file);
        } 

        textures.insert({sprite, tex});
    } 

    entities.insert({entity.name, {entity.name, entity.x, entity.y, textures[sprite]}});
} 

TEABAG_INTERNAL_END

TEABAG_NS_END
