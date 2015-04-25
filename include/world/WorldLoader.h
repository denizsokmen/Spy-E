//
// Created by Taha Doğan Güneş on 13/03/15.
//

#ifndef _SPYE_WORLDLOADER_H_
#define _SPYE_WORLDLOADER_H_

#include <glm/glm.hpp>
#include "utils/XMLLoader.h"
#include <string>

#define SPYE_WORLD_FILE_EXTENSION ".xml"
#define ENTITIES_FOLDER_NAME "entities"

class World;
class ObjLoader;
class EntityLoader;

class WorldLoader : public XMLLoader {

private:
    EntityLoader* entityLoader;
    rapidxml::xml_node<> *worldNode;
    std::string folderPath;
    std::string entitiesFolderPath;

    void parseWorldNode();
    void parseNameNode();
    void parseVersionNode();
    void parseEntities();
    void parseEntity(rapidxml::xml_node<> *entityNode);
    glm::vec3 parsePosition(rapidxml::xml_node<> *entityNode);
    glm::vec3 parseColor(rapidxml::xml_node<> *entityNode);

    void getComponent(rapidxml::xml_node<> *positionNode,
                      const char *name, float *value);

public:
    World* world;
    WorldLoader(World* world);
    void load(char const *name);

    ~WorldLoader();

};


#endif //_SPYE_WORLDLOADER_H_
