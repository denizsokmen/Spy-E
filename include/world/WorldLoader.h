//
// Created by Taha Doğan Güneş on 13/03/15.
//

#ifndef _SPYE_WORLDLOADER_H_
#define _SPYE_WORLDLOADER_H_

class World;
class ObjLoader;
class EntityLoader;

class WorldLoader {

private:
    World* world;
    EntityLoader* entityLoader;

public:
    WorldLoader(World* world);

    void load(char const *name);

    ~WorldLoader();

};


#endif //_SPYE_WORLDLOADER_H_
