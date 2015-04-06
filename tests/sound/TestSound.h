//
// Created by Taha Doğan Güneş on 18/03/15.
//

#ifndef _SPYE_SOUNDSYSTEM_H_
#define _SPYE_SOUNDSYSTEM_H_

#include "logic/System.h"

class ShaderProgram;
class VertexBuffer;
class Game;
class SoundManager;

class SoundSystem: public System {
   Game *game;

public:
   SoundSystem(Game *game);

   void update(float dt);
   void draw();

   ShaderProgram *generalShader;

   void draw2D();
   VertexBuffer *vbo;

};
#endif //_SPYE_SOUNDSYSTEM_H_
