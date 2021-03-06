#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "logic/System.h"
#include "physics/Physics.h"

class Entity;
class Game;
class Renderable;
class ShaderProgram;
class VertexBuffer;
class Skybox;
class Light;
class Billboard;

class FontSDL;

class TestGameSystem: public System {
    Renderable* entity;
	Game *game;

public:
    Physics* physics;
    Body* box;
	Light *charlight;

    TestGameSystem(Game *game);

    void update(float dt);
    void draw();
	void init(){}

    ShaderProgram *generalShader;

    void draw2D();

    VertexBuffer *vbo;
    FontSDL *font;

    void assignKeyboardInputs(Game *game);
    void assignMouseInputs(Game *game);

    Skybox *skybox;
    Billboard *billboard;
};


#endif