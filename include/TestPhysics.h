//
// Created by Enes Şenel on 13/03/15.
//

#ifndef _SPYE_TESTPHYSICS_H_
#define _SPYE_TESTPHYSICS_H_

#include "logic/System.h"
#include <logic/Game.h>
#include "graphics/Mesh.h"
#include "graphics/ObjLoader.h"
#include "graphics/Renderable.h"
#include "world/Scene.h"
#include "input/KeyboardButtonHandler.h"
#include "input/MouseButtonHandler.h"
#include "graphics/Shader.h"
#include "graphics/Cube.h"
#include "world/Camera.h"
#include "physics/PhysicsWorld.h"

class ShaderProgram;
class VertexBuffer;
class Game;

class TestPhysics: public System {
    Renderable* entity;
    Game *game;

public:

    float horizontalAngle = 3.14f;
    float verticalAngle = 0.0f;
    float mouseSpeed = 0.005f;
    float speed = 10.0f;

    TestPhysics(Game *game);
    ~TestPhysics();

    void update(float dt);
    void draw();

    ShaderProgram *generalShader;

    void draw2D();
    VertexBuffer *vbo;
};


#endif //_SPYE_TESTPHYSICS_H_
