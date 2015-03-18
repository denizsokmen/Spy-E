//
// Created by Enes Şenel on 13/03/15.
//

#ifndef _SPYE_ENTITYLOADER_H_
#define _SPYE_ENTITYLOADER_H_

#include <string>
#include "utils/rapidxml.hpp"

class Entity;
class ObjLoader;

class EntityLoader {

public:
    EntityLoader();
    Entity* load(char const *name, World* world);

    ~EntityLoader();

private:
    ObjLoader *objLoader;

};


#endif //_SPYE_ENTITYLOADER_H_
