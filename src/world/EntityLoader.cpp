
#include <glm/glm.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

//from Spy-E Engine
#include "world/Entity.h"
#include "graphics/Mesh.h"
#include "world/World.h"
#include "world/EntityLoader.h"
#include "graphics/ObjLoader.h"
#include "graphics/Renderable.h"
#include "utils/rapidxml_utils.hpp"
#include "Constants.h"

EntityLoader::EntityLoader(){
    objLoader = new ObjLoader();
    document = NULL;
}


Entity* EntityLoader::load(char const *name, World* world){
    Entity *entity = NULL;

    std::string entityName(name);
    std::string path = this->getPath(entityName);
    document = this->getDocument(path.c_str());


    rapidxml::xml_node<> *rootNode = document->first_node("Entity");
    std::string type(rootNode->first_node("Type")->value());
    printf("    Type: %s\n", type.c_str());


    if (type == "Mesh")
        return world->createRenderable(name);


    return entity;
}


std::string EntityLoader::getPath(std::string entityName) {
    return std::string(ENTITIES_DIR) + entityName + PATH_SEPARATOR + entityName + ".xml";
}


EntityLoader::~EntityLoader() {
    document->clear();
}
