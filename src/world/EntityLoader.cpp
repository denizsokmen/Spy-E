
#include <glm/glm.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <utils/FileOperations.h>

//from Spy-E Engine
#include "world/Entity.h"
#include "graphics/Mesh.h"
#include "world/World.h"
#include "world/EntityLoader.h"
#include "resource/ObjLoader.h"
#include "graphics/Renderable.h"
#include "utils/rapidxml_utils.hpp"
#include "Constants.h"

EntityLoader::EntityLoader(){
    objLoader = new ObjLoader();

}


Entity* EntityLoader::load(char const *name, World* world){
    std::string entityName(name);
    std::vector<std::string> directories = FileOperations::getAllDirectories("./assets/entities/");

    if (std::find(directories.begin(), directories.end(), entityName) != directories.end()){
        return world->createRenderable(name);
    }
    printf("[EntityLoader] Unknown entity named as %s\n", name);

    return NULL;
}


std::string EntityLoader::getPath(std::string entityName) {
    return std::string(ENTITIES_DIR) + entityName + PATH_SEPARATOR + entityName + ".xml";
}


EntityLoader::~EntityLoader() {

}
