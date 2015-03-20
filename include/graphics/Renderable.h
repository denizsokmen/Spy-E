#ifndef __Agile__Renderable__
#define __Agile__Renderable__

#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "world/Entity.h"


class VertexBuffer;
class Mesh;
class Renderer;

class Renderable : public Entity {

protected:


public:
    Renderable();
    Mesh* mesh;
    unsigned int identifier;

    ~Renderable();
    virtual void render(Renderer *renderer);
//    void load(); FIXME: Someone should make a decision whether to keep them or delete them.
//    void unload();

    VertexBuffer* getVertexBuffer();



};


#endif /* defined(__Agile__Renderable__) */
