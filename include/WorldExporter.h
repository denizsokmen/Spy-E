#ifndef WORLDEXPORT_H_INC
#define WORLDEXPORT_H_INC

#include <string>
#include "tinyxml2.h"

class World;
class Entity;

class WorldExporter {

private:
    tinyxml2::XMLDocument xmlDocument;
    tinyxml2::XMLNode* rootNode;
    void addTextElement(const char* key , const char *value);
    void saveEntities(World *world);


public:
    WorldExporter();
    //returns true if the world is saved successfully
    bool save(std::string mapName, std::string mapVersion, std::string path, World* world);
    tinyxml2::XMLElement *saveEntity(Entity *&entity);
};

#endif