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


WorldLoader::WorldLoader() {


}

World* WorldLoader::load(char const *path) {
    tinyxml2::XMLDocument xmlDocument;

    printf("Loading world from '%s'\n", path);
    tinyxml2::XMLError error = xmlDocument.LoadFile(path);
    printf("Loading world from '%s'\n", path);

    if (error != tinyxml2::XML_NO_ERROR) {
        printf("Unable to load world from '%s' with error: %i \n", path, error);
        return NULL;
    }
//
//    tinyxml2::XMLNode* worldNode = xmlDocument.FirstChild();
//    tinyxml2::XMLElement* nameElement = worldNode->FirstChildElement("Name");
//    tinyxml2::XMLElement* versionElement = worldNode->FirstChildElement("Version");
//    tinyxml2::XMLElement* entitiesElement = worldNode->FirstChildElement("Entities");
//    tinyxml2::XMLElement* entityElement = entitiesElement->FirstChildElement("Entity");
//
//    printf("Name: %s\n",nameElement->GetText());
//    printf("Version: %s\n",versionElement->GetText());
//
//    world = new World();
//    ObjLoader* objLoader = new ObjLoader();
//
//
//    while (entityElement != NULL) {
//        tinyxml2::XMLElement* positionElement = entityElement->FirstChildElement("Position");
//
//        float x, y, z;
//        tinyxml2::XMLElement* xPosition = positionElement->FirstChildElement("X");
//        tinyxml2::XMLElement* yPosition = positionElement->FirstChildElement("Y");
//        tinyxml2::XMLElement* zPosition = positionElement->FirstChildElement("Z");
//
//
//        xPosition->QueryFloatText(&x);
//        yPosition->QueryFloatText(&y);
//        zPosition->QueryFloatText(&z);
//
//        glm::vec3 position = glm::vec3(x,y,z);
//
//        Mesh* mesh = new Mesh();
//        mesh->setVertexBuffer(objLoader->loadOBJ("./assets/entities/camera/camera-bottom.obj"));
//
//        Renderable* entity = world->createRenderable();
//        entity->setPosition(position);
//        entity->mesh = mesh;
//        entityElement = entitiesElement->NextSiblingElement("Entity");
//    }
//
//
//
//    return world;
}
