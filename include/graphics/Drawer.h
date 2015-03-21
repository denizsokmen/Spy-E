//
// Created by deniz on 21/03/15.
//

#ifndef _SPYE_DRAWER_H_
#define _SPYE_DRAWER_H_
#include <vector>
#include <glm/glm.hpp>

class Drawable;
class Game;
class ShaderProgram;
class VertexBuffer;

class DrawObj {

public:
    Drawable* drawable;
    glm::vec2 position;
    glm::vec3 color;
    glm::vec2 size;
};

class Drawer {


    std::vector<DrawObj> drawList;
	ShaderProgram *quadShader;
	VertexBuffer *quadBuffer;

public:
    void draw(Drawable*, glm::vec2 pos);
    void drawAll();

    Game* game;
};


#endif //_SPYE_DRAWER_H_
