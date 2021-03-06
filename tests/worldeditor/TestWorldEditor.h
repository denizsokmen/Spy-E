//
// Created by Taha Doğan Güneş on 18/03/15.
//

#ifndef _SPYE_WORLDEDITORSYSTEM_H_
#define _SPYE_WORLDEDITORSYSTEM_H_


#include "logic/System.h"

class ShaderProgram;
class VertexBuffer;
class Game;
class SoundManager;
class Billboard;
//class FontSDL;

class WorldEditorSystem: public System {

    Game *game;
    GLuint vertexbuffer;

public:
    WorldEditorSystem(Game *game);


    void update(float dt);
    void draw();

    ShaderProgram *generalShader;

    void draw2D();
    VertexBuffer *vbo;


//    FontSDL *font;
    Billboard *billboard;
};


#endif //_SPYE_WORLDEDITORSYSTEM_H_
