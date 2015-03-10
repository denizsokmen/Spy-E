#ifndef WORLDLOADER_H_INC
#define WORLDLOADER_H_INC

#include <string>
#include "tinyxml2.h"

class World;
class Entity;

class WorldLoader {

public:
    WorldLoader();
    //Return null if it is impossible to load the world
    World* load(std::string path);

};

#endif