
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
}


Entity* EntityLoader::load(char const *name, World* world){

    return world->createRenderable(name);



}


std::string EntityLoader::getPath(std::string entityName) {
    return std::string(ENTITIES_DIR) + entityName + PATH_SEPARATOR + entityName + ".xml";
}


EntityLoader::~EntityLoader() {

}
