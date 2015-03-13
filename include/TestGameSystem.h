#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "logic/System.h"
class Entity;
class Game;
class Renderable;

class TestGameSystem: public System {
    Renderable* entity;
	Game *game;

public:
    TestGameSystem(Game *game);

    void update(float dt);
    void draw();

};


#endif