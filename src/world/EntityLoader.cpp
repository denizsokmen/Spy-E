#include <glm/glm.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <Constants.h>


#include "world/Entity.h"
#include "graphics/Mesh.h"
#include "world/World.h"
#include "world/EntityLoader.h"
#include "graphics/ObjLoader.h"
#include "graphics/Renderable.h"
#include "utils/rapidxml_utils.hpp"



EntityLoader::EntityLoader(){
    objLoader = new ObjLoader();
}



Entity* EntityLoader::load(char const *name, World* world){
    std::string entityName(name);
    std::string path = std::string(ENTITIES_DIR) + entityName + "/" + entityName + ".xml";
    printf("Loading file: %s \n", path.c_str());

    Entity *entity = NULL;

    std::ifstream file (path.c_str());
    std::string tmp;
    if (!(file >> tmp)) return NULL;



    rapidxml::file<> xmlFile(path.c_str()); // Default template is char
    rapidxml::xml_document<> document;
    document.parse<0>(xmlFile.data());


    rapidxml::xml_node<>* rootNode = document.first_node("Entity");

    std::string type(rootNode->first_node("Type")->value());
    printf("    ");
    printf("Type: %s\n",type.c_str());

    if (entityName == "Cube") {

    }


    if (type == "Mesh") {
        return world->createRenderable(name);
    }

    // else if ...



    return entity;
}

EntityLoader::~EntityLoader(){

}

