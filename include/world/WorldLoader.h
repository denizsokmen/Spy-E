//
// Created by Taha Doğan Güneş on 13/03/15.
//

#ifndef _SPYE_WORLDLOADER_H_
#define _SPYE_WORLDLOADER_H_



class World;

class WorldLoader {

private:
    World* world;

public:

    WorldLoader();

    World* load(const char* path);



};


#endif //_SPYE_WORLDLOADER_H_
