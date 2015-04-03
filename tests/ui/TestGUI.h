//
// Created by Taha Doğan Güneş on 03/04/15.
//

#ifndef SPYE_TESTGUI_H
#define SPYE_TESTGUI_H

#include "logic/System.h"
#include "physics/PhysicsWorld.h"
#include "physics/Body.h"

class Entity;

class Game;

class Renderable;

class ShaderProgram;

class VertexBuffer;

class FPS;

class FontSDL;

class TestGUI : public System {
    Renderable *entity;
    Game *game;

public:
    PhysicsWorld *physicsWorld;
    Body *box;

    TestGUI(Game *game);

    void update(float dt);

    void draw();

    void init() { }

    ShaderProgram *generalShader;

    void draw2D();

    VertexBuffer *vbo;
    FPS *fps;
    FontSDL *font;

    void assignKeyboardInputs(Game *game);

    void assignMouseInputs(Game *game);
};


#endif //SPYE_TESTGUI_H