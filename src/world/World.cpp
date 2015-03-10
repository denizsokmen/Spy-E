#include <vector>
#include "graphics/Renderable.h"
#include "world/World.h"


int World::getEntityCount() {
    return entities.size();
}

Renderable* World::createRenderable() {
    Renderable* entity = new Renderable();
    renderables.push_back(entity);
    return entity;
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

std::vector<Renderable *> World::getRenderables() {
    return renderables;
}
