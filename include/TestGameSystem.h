#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "System.h"
class Entity;
class Game;
class Renderable;

class TestGameSystem: public System {
    Renderable* entity;

public:
    TestGameSystem(Game *game);

    void update(float dt);
    void draw();

};


#endif