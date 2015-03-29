#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "logic/System.h"
class Entity;
class Game;
class Renderable;
class ShaderProgram;
class VertexBuffer;

class TestGameSystem: public System {
    Renderable* entity;
	Game *game;

public:
    TestGameSystem(Game *game);

    void update(float dt);
    void draw();
	void init(){}

    ShaderProgram *generalShader;

    void draw2D();

    VertexBuffer *vbo;
};


#endif