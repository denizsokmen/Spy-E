// https://gist.github.com/JSchaenzle/2726944


#include "world/World.h"
#include "world/Entity.h"
#include "world/WorldLoader.h"
#include "world/EntityLoader.h"
#include <glm/glm.hpp>
#include <graphics/Mesh.h>
#include "resource/ObjLoader.h"
#include "graphics/Renderable.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <utils/rapidxml_utils.hpp>
#include <vector>
#include <utils/FileOperations.h>
#include "Constants.h"

WorldLoader::WorldLoader(World* world) {
    this->world = world;
    this->entityLoader = new EntityLoader();
    this->worldNode = NULL;
}


/* WorldLoader::load function gets path of the World folder:
 * For instance:
 * ~/Spy-E/Level1/ includes inside
 * ~/Spy-E/Level1/Level1.xml
 * ~/Spy-E/Level1/entities/
 * ~/Spy-E/Level1/entities/cube/
 * ~/Spy-E/Level1/entities/cube/cube.obj
 * ~/Spy-E/Level1/entities/cube/cube.mtl
 * ...
 * So:
 *  if path == "~/Spy-E/Level1/" then:
 *      documentPath = "~/Spy-E/Level1/Level1.xml"
 *      folderPath = "~/Spy-E/Level1/"
 */
void WorldLoader::load(char const *path) {


    printf("---------- WorldLoader -------------\n");
    printf("[WorldLoader] Loading world from folder: %s \n", path);
    this->folderPath = path;


    std::string folderPathWithoutSeperator(path);
    folderPathWithoutSeperator.pop_back();


    int beginIdx = folderPathWithoutSeperator.rfind(PATH_SEPARATOR);
    std::string worldName = folderPathWithoutSeperator.substr(beginIdx + 1);
    printf("world name: %s\n", worldName.c_str());
    std::string documentPath = folderPath + worldName +  SPYE_WORLD_FILE_EXTENSION;

    this->entitiesFolderPath = this->folderPath  + ENTITIES_FOLDER_NAME + PATH_SEPARATOR;

    rapidxml::xml_document<> *document = this->getDocument(documentPath.c_str());
    if (document != NULL) {
        worldNode = document->first_node("World");
        this->parseWorldNode();
    }

}


void WorldLoader::parseWorldNode() {
    if (worldNode == NULL) {
        printf("[WorldLoader] <World> node is not found!\n");
        return;
    }
    this->parseNameNode();
    this->parseVersionNode();
    this->parseEntities();

}

void WorldLoader::parseNameNode() {
    rapidxml::xml_node<> *nameNode = worldNode->first_node("Name");
    if (nameNode == NULL) {
        printf("[WorldLoader] <Name> node is not found!\n");
        return;
    }
    world->setName(nameNode->value());
}

void WorldLoader::parseVersionNode() {
    rapidxml::xml_node<> *versionNode = worldNode->first_node("Version");
    if (versionNode == NULL) {
        printf("[WorldLoader] <Version> node is not found!\n");
        return;
    }
    world->setVersion(versionNode->value());
}


void WorldLoader::parseEntities() {
    rapidxml::xml_node<> *entitiesNode = worldNode->first_node("Entities");
    if (entitiesNode == NULL) {
        printf("[WorldLoader] <Entities> node is not found!\n");
        return;
    }

    for (rapidxml::xml_node<> *entityNode = entitiesNode->first_node(
            "Entity"); entityNode; entityNode = entityNode->next_sibling())
        this->parseEntity(entityNode);
}


void WorldLoader::parseEntity(rapidxml::xml_node<> *entityNode) {
    rapidxml::xml_attribute<> *nameNode = entityNode->first_attribute("name");
    if (nameNode == NULL) {
        printf("[WorldLoader] <Entity> does not have a name attribute!\n");
        return;
    }

    rapidxml::xml_node<> *typeNode = entityNode->first_node("Type");
    if (typeNode == NULL) {
        printf("[WorldLoader] <Entity> does not have a type <Type> node!\n");
        return;
    }

    std::string entityFolder = this->entitiesFolderPath + typeNode->value() + PATH_SEPARATOR;
    std::string entityName = typeNode->value();
    std::string entityPath = entityFolder + entityName + OBJ_EXTENSION;

    std::vector<std::string> directories = FileOperations::getAllDirectories(this->entitiesFolderPath);

    Entity *entity = NULL;
    if (std::find(directories.begin(), directories.end(), entityName) != directories.end()){
        entity = entityLoader->load(entityPath.c_str(), world);
    }
    else {
        printf("[WorldLoader] Unknown entity named as %s (not found in entitiesFolder) \n", entityName.c_str());
    }


    if (entity != NULL) {
        printf("[WordLoader] Loading '%s'.\n", nameNode->value());
		entity->setPosition(this->parsePosition(entityNode));
		entity->setColor(this->parseColor(entityNode));

    }
    else {
        printf("[WordLoader] Unable to load '%s'.\n", nameNode->value());
    }

}

glm::vec3 WorldLoader::parsePosition(rapidxml::xml_node<> *entityNode) {
    rapidxml::xml_node<> *positionNode = entityNode->first_node("Position");
    if (positionNode == NULL) {
        printf("[WorldLoader] Warning: <Entity> does not have a <Position> node!\n");
        return glm::vec3(0, 0, 0);
    }
    float x = 0, y = 0, z = 0;

    this->getComponent(positionNode, "X", &x);
    this->getComponent(positionNode, "Y", &y);
    this->getComponent(positionNode, "Z", &z);

    return glm::vec3(x, y, z);
}

glm::vec3 WorldLoader::parseColor(rapidxml::xml_node<> *entityNode) {
    rapidxml::xml_node<> *colorNode = entityNode->first_node("Color");
    if (colorNode == NULL) {
        //printf("[WorldLoader] Optional: <Entity> does not have a <Color> node!\n");
        return glm::vec3(1, 1, 1);
    }
    float r = 0, g = 0, b = 0;

    this->getComponent(colorNode, "R", &r);
    this->getComponent(colorNode, "G", &g);
    this->getComponent(colorNode, "B", &b);

    return glm::vec3(r, g, b);
}

void WorldLoader::getComponent(rapidxml::xml_node<> *mainNode,
                               const char *name, float *value) {
    rapidxml::xml_node<> *componentNode = mainNode->first_node(name);
    if (componentNode == NULL) {
        printf("[WorldLoader] Warning: MainNode does not have a <%s> node!\n", name);
        return;
    }
    std::stringstream stringstream(componentNode->value());

    if (!(stringstream >> *value)) {
        printf("[WorldLoader] Warning: <%s> node's value is not a valid float value!\n", name);
        return;
    }
}


WorldLoader::~WorldLoader(){
    printf("[WorldLoader] Deallocating...\n");
    delete this->document;
    delete this->file;
    delete this->entityLoader;

    printf("------------------------------------\n");
}



