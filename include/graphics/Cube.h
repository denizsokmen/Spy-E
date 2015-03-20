

#ifndef _SPYE_CUBE_H_
#define _SPYE_CUBE_H_


#include "graphics/Renderable.h"

class Renderer;

class Cube: public Renderable {


public:
    Cube();
    ~Cube();
    glm::vec3 color;
    void render(Renderer *renderer);

};


#endif //_SPYE_CUBE_H_
