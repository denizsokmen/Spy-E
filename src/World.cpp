#include <vector>
#include "Entity.h"
#include "World.h"


int World::getEntityCount() {
    return entities.size();
}

std::vector<Entity*> World::getEntities() {
    return entities;
}
Entity* World::getEntity(int identifier) {
    return entities[identifier];
}

void World::addEntity(Entity *entity) {
    this->entities.push_back(entity);
}

Entity* World::createEntity() {
    Entity* entity = new Entity();
    entities.push_back(entity);
    return entity;
}

void World::addEntities(std::vector<Entity *> *entities) {
    for(auto &entity: *entities) {
        this->addEntity(entity);
    }
}
