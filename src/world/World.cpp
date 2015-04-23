#include <vector>
#include "graphics/Renderable.h"
#include "world/World.h"
#include "graphics/Mesh.h"
#include "resource/ObjLoader.h"
#include "Constants.h"
#include "resource/ResourceManager.h"
int World::getEntityCount() {
    return entities.size();
}

Renderable* World::createRenderable(const char* name) {
    std::string entityName(name);
    Renderable* entity = new Renderable();
    std::string modelPath = ENTITIES_DIR+entityName+PATH_SEPARATOR+entityName+OBJ_EXTENSION;
	Mesh* mesh = ResourceManager::instance()->createMesh(modelPath.c_str()).get(); // objLoader->loadOBJ(modelPath.c_str());
    //VertexBuffer *buffer = objLoader->loadOBJ(modelPath.c_str());
    //mesh->setVertexBuffer(buffer);
    entity->mesh = mesh;


    renderables.push_back(entity);
    return entity;
}



Renderable* World::createRenderableFromPath(const char* modelPath) {
    Renderable* entity = new Renderable();
    Mesh* mesh = ResourceManager::instance()->createMesh(modelPath).get(); // objLoader->loadOBJ(modelPath.c_str());
    //VertexBuffer *buffer = objLoader->loadOBJ(modelPath.c_str());
    //mesh->setVertexBuffer(buffer);
    entity->mesh = mesh;

    renderables.push_back(entity);
    return entity;
}


std::vector<Entity*>& World::getEntities() {
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

std::vector<Renderable *>& World::getRenderables() {
    return renderables;
}

World::World() {
    objLoader = new ObjLoader();
}

World::~World() {
    delete objLoader;
}

std::string World::getName() {
    return name;
}

void World::setName(std::string name) {
    this->name = name;
}

std::string World::getVersion() {
    return version;
}

void World::setVersion(std::string version) {
    this->version = version;
}
