#include "inc/world.hpp"

TEABAG_NS

void World::loadLevel(std::string name) {
    std::string file = TEABAG_MAP_TEA(name);

    internal::Reader reader(file);
    if(!reader) {
        throw FileOpenError(file);
    } 

    while(reader.nextLine()) {
        std::string option;
        if(!reader.get(option)) {
            throw LineReadError(file, reader.line);
        } 

        if(option == "tile") {
            int r, g, b;
            std::string name;
            bool blocking;

            if(!reader.get(r, g, b, name, blocking)) {
                throw LineReadError(file, reader.line);
            } 

            map.tiles().queueTile(name, r, g, b, blocking);
        } 
        else if(option == "entity") {
            std::string name;
            int x, y;

            if(!reader.get(name, x, y)) {
                throw LineReadError(file, reader.line);
            } 

            entityManager.queueEntity(name, x, y);
        } 
    } 

    map.tiles().loadQueue();
    map.loadMap(name);

    entityManager.loadQueue();
} 

Entity& World::entity(std::string name) {
    if(entityManager.entities.find(name) == entityManager.entities.end()) {
        throw NoSuchEntityError(name);
    } 

    return entityManager.entities.at(name);
} 

void World::render(sf::RenderWindow& window) {
    window.draw(map.mapSprite);

    for(auto& entityPair : entityManager.entities) {
        window.draw(entityPair.second.sprite);
    } 
} 

TEABAG_NS_END
