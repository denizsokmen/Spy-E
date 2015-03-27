//
// Created by deniz on 27/03/15.
//

#ifndef SPYE_SPYE_H
#define SPYE_SPYE_H

#include <logic/System.h>

class Game;

class SpyE : public System {

public:

    SpyE(Game *game);

    Game *game;

    void update(float dt);

    void init();
};


#endif //SPYE_SPYE_H
