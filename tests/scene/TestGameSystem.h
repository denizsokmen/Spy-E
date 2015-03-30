#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "logic/System.h"
#include "physics/PhysicsWorld.h"
#include "physics/Body.h"
class Entity;
class Game;
class Renderable;
class ShaderProgram;
class VertexBuffer;

class TestGameSystem: public System {
    Renderable* entity;
	Game *game;

public:
    PhysicsWorld* physicsWorld;
    Body* box;

    TestGameSystem(Game *game);

    void update(float dt);
    void draw();
	void init(){}

    ShaderProgram *generalShader;

    void draw2D();

    VertexBuffer *vbo;

    void assignKeyboardInputs(Game *game);

    void assignMouseInputs(Game *game);
};


#endif