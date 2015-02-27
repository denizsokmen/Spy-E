#include <vector>
#include "Entity.h"
#include "World.h"


int World::getEntityCount() {
    return entities.size();
}

Entity* World::getEntity(int identifier) {
    return entities[identifier];
}

void World::addEntity(Entity *entity) {
    this->entities.push_back(entity);
}

void World::addEntities(std::vector<Entity *> *entities) {
    for(auto &entity: *entities) {
        this->addEntity(entity);
    }
}
