//
// Created by Taha Doğan Güneş on 05/04/15.
//

#ifndef SPYE_TESTMENU_H
#define SPYE_TESTMENU_H

#include "logic/System.h"
#include "physics/PhysicsWorld.h"
#include "physics/Body.h"

class Entity;

class Game;

class Renderable;

class ShaderProgram;

class VertexBuffer;

class Label;

class FontSDL;

class TestMenu : public System {


    Renderable *entity;
    Game *game;

private:
    Label *fpsLabel;

public:
    Body *box;
    VertexBuffer *vbo;
    FontSDL *font;
    ShaderProgram *generalShader;

    TestMenu(Game *game);

    void update(float dt);

    void draw();

    void init() { }

    void draw2D();

    void assignKeyboardInputs(Game *game);

    void assignMouseInputs(Game *game);
};


#endif //SPYE_TESTMENU_H
