// https://gist.github.com/JSchaenzle/2726944


#include "world/World.h"
#include "world/Entity.h"
#include "world/WorldLoader.h"
#include "world/EntityLoader.h"
#include <glm/glm.hpp>
#include <graphics/Mesh.h>
#include "graphics/ObjLoader.h"
#include "graphics/Renderable.h"
#include "utils/rapidxml.hpp"

#include <fstream>
#include <vector>
#include <iostream>
#include <graphics/Cube.h>


WorldLoader::WorldLoader(World* world) {
    this->world = world;
    this->entityLoader = new EntityLoader();
}

void WorldLoader::load(char const *path) {
    printf("---------- WorldLoader -------------\n");
    printf("Loading file: %s \n", path);

    rapidxml::xml_document<> document;
    std::ifstream file (path);
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');
    document.parse<0>(&buffer[0]);
    rapidxml::xml_node<>* rootNode = document.first_node("World");



    printf("Name: %s\n",rootNode->first_node("Name")->value());
    printf("Version: %s\n",rootNode->first_node("Version")->value());


    rapidxml::xml_node<>* entities = rootNode->first_node("Entities");


    for (rapidxml::xml_node<> *entityNode = entities->first_node("Entity"); entityNode; entityNode = entityNode->next_sibling())
    {
        printf("Entity: Name'%s' \n", entityNode->first_attribute("name")->value());
        printf("        Type:'%s' \n", entityNode->first_node("Type")->value());
        rapidxml::xml_node<>* positionNode = entityNode->first_node("Position");
        float x = (float) atof(positionNode->first_node("X")->value());
        float y = (float) atof(positionNode->first_node("Y")->value());
        float z = (float) atof(positionNode->first_node("Z")->value());
        printf("    ");
        printf("x:%f y:%f z:%f \n",x,y,z);

        glm::vec3 position = glm::vec3(x,y,z);

        Entity* entity = entityLoader->load(entityNode->first_node("Type")->value(), world);
        entity->name = entityNode->first_attribute("name")->value();
        //TODO: Must get color for cube's
        if (entity) {
            entity->setPosition(position);
            if(Cube *cube = dynamic_cast<Cube*>(entity)) {
                rapidxml::xml_node<>* colorNode = entityNode->first_node("Color");
                float r = (float) atof(positionNode->first_node("R")->value());
                float g = (float) atof(positionNode->first_node("G")->value());
                float b = (float) atof(positionNode->first_node("B")->value());
                printf("    ");
                printf("r:%f b:%f g:%f \n",r,g,b);

                glm::vec3 color = glm::vec3(r,g,b);
                cube->color = color;
            }

        }
        else {
            printf("Unable to load %s.\n",entityNode->first_attribute("name")->value());
        }


    }




    printf("------------------------------------\n");
}

WorldLoader::~WorldLoader(){

}