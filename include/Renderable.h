//
//  Renderable.h
//  Agile
//
//  Created by Taha Doğan Güneş on 17/02/15.
//  Copyright (c) 2015 CS476. All rights reserved.
//

#ifndef __Agile__Renderable__
#define __Agile__Renderable__

#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Entity.h"


class VertexBuffer;
class Mesh;

class Renderable : public Entity {
public:

protected:


public:
    Renderable();
    Mesh* mesh;
    unsigned int identifier;

    virtual ~Renderable() {}
    virtual void render() {}
    virtual void load() {}
    virtual void unload() {}

    VertexBuffer* getVertexBuffer();



};


#endif /* defined(__Agile__Renderable__) */
