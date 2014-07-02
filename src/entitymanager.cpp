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
        loadTexture(sprite);
    } 

    entities.insert({entity.name, {entity.name, entity.x, entity.y, textures[sprite]}});
} 

void EntityManager::loadTexture(std::string name) {
    std::string file = TEABAG_SPRITE_IMG(name);

    sf::Texture tex;
    if(!tex.loadFromFile(file)) {
        throw FileOpenError(file);
    } 

    int w = tex.getSize().x;
    int h = tex.getSize().y;

    file = TEABAG_SPRITE_TEA(name);

    internal::Reader reader(file);
    if(reader) {
        while(reader.nextLine()) {
            std::string option;
            if(!reader.get(option)) {
                throw LineReadError(file, reader.line);
            } 

            if(option == "size") {
                if(!reader.get(w, h)) {
                    throw LineReadError(file, reader.line);
                } 
            } 
        } 
    } 

    textures.insert({name, {tex, w, h}});
}

TEABAG_INTERNAL_END

TEABAG_NS_END
