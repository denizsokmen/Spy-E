//
// Created by deniz on 27/03/15.
//

#ifndef SPYE_SPYE_H
#define SPYE_SPYE_H

#include <logic/System.h>

class Renderable;
class Game;
class ShaderProgram;
class VertexBuffer;
class Skybox;

class SpyE : public System {

public:
    bool active;
    SpyE(Game *game);

    Game *game;

    void update(float dt);
    void init();
	void draw();

    Renderable *entity;
	Skybox *skybox;

    void activate();

    ShaderProgram *generalShader;
    VertexBuffer *vbo;
};


#endif //SPYE_SPYE_H
