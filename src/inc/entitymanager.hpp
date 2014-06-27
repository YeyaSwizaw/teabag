#ifndef TEABAG_ENTITYMANAGER_HPP
#define TEABAG_ENTITYMANAGER_HPP

#include "defines.hpp"
#include "reader.hpp"
#include "error.hpp"
#include "entity.hpp"

#include <string>
#include <vector>
#include <unordered_map>

#include <SFML/Graphics.hpp>

TEABAG_NS

class World;

TEABAG_INTERNAL

struct EntityInfo {
    std::string name;
    int x, y;
}; 

class EntityManager {
private:
    friend class teabag::World;

    EntityManager();

    void queueEntity(std::string name, int x, int y);
    void loadQueue();
    void loadEntity(EntityInfo& entity);

    std::vector<EntityInfo> entityQueue;

    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, teabag::Entity> entities;
};

TEABAG_INTERNAL_END

TEABAG_NS_END

#endif
