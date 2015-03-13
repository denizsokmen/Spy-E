//
// Created by Taha Doğan Güneş on 13/03/15.
//

#ifndef _SPYE_WORLDLOADER_H_
#define _SPYE_WORLDLOADER_H_




class World;
class ObjLoader;

class WorldLoader {

private:
    World* world;
    ObjLoader* objLoader;

public:
    WorldLoader(World* world);

    void load(const char* path);



};


#endif //_SPYE_WORLDLOADER_H_
