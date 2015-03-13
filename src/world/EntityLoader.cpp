#include <glm/glm.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>


#include "world/Entity.h"
#include "graphics/Mesh.h"
#include "world/World.h"
#include "world/EntityLoader.h"
#include <graphics/Objloader.h>
#include "graphics/Renderable.h"


#define ENTITIES_DIR "./assets/entities/"

EntityLoader::EntityLoader(){
    objLoader = new ObjLoader();
}



Entity* EntityLoader::load(char const *name){
    rapidxml::xml_document<> document;
    std::string path = std::string(ENTITIES_DIR) + std::string(name) + "/" + std::string(name) + ".xml";
    Entity *entity = NULL;

    std::ifstream file (path.c_str());
    std::string tmp;
    if (!(file >> tmp)) return NULL;

    printf("Loading file: %s \n", path.c_str());

    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');
    document.parse<rapidxml::parse_validate_closing_tags>(&buffer[0]);

    rapidxml::xml_node<>* rootNode = document.first_node("Entity");

    std::string type(rootNode->first_node("Type")->value());
    printf("Type: %s\n",type.c_str());


    if (type == "Mesh") {
        Renderable *renderable = new Renderable();
        Mesh* mesh = new Mesh();
        std::string modelPath = std::string(ENTITIES_DIR) + std::string(name) + "/" +  std::string(name) + ".obj";
        mesh->setVertexBuffer(objLoader->loadOBJ(modelPath.c_str()));
        renderable->mesh = mesh;
        entity = renderable;
    }

    // else if ...



    return entity;
}

EntityLoader::~EntityLoader(){

}

