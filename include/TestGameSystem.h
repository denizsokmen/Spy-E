#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "System.h"
class Entity;
class Game;

class TestGameSystem: public System {
    Entity* entity;

public:
    TestGameSystem(Game *game);

    void update(float dt);
    void draw();

};


#endif