//
// Created by Taha Doğan Güneş on 13/03/15.
//



#include "world/World.h"
#include "world/Entity.h"
#include "world/WorldLoader.h"
#include <glm/glm.hpp>
#include <graphics/Mesh.h>
#include <graphics/Objloader.h>
#include "graphics/Renderable.h"
#include "utils/rapidxml.hpp"

#include <fstream>
#include <vector>
#include <iostream>


WorldLoader::WorldLoader(World* world) {
    this->world = world;
    objLoader = new ObjLoader();
}

void WorldLoader::load(char const *path) {
    rapidxml::xml_document<> document;
    std::ifstream file (path);



    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');

    document.parse<0>(&buffer[0]);

    rapidxml::xml_node<>* rootNode = document.first_node("World");


    printf("---------- WorldLoader -------------\n");
    printf("Name: %s\n",rootNode->first_node("Name")->value());
    printf("Version: %s\n",rootNode->first_node("Version")->value());




    rapidxml::xml_node<>* entities = rootNode->first_node("Entities");


    for (rapidxml::xml_node<> *entityNode = entities->first_node("Entity"); entityNode; entityNode = entityNode->next_sibling())
    {
        printf("Entity: \n");
        rapidxml::xml_node<>* positionNode = entityNode->first_node("Position");
        float x = (float) atof(positionNode->first_node("X")->value());
        float y = (float) atof(positionNode->first_node("Y")->value());
        float z = (float) atof(positionNode->first_node("Z")->value());
        printf("    ");
        printf("x:%f y:%f z:%f \n",x,y,z);



        glm::vec3 position = glm::vec3(x,y,z);

        Mesh* mesh = new Mesh();
        mesh->setVertexBuffer(objLoader->loadOBJ("./assets/entities/camera/camera-bottom.obj"));
        Renderable* entity = world->createRenderable();
        entity->setPosition(position);
        entity->mesh = mesh;
    }




    printf("------------------------------------\n");


}
