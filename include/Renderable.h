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


class VertexBuffer;

class Renderable {

private:


    
protected:
    //glm::vec3 position;
    glm::mat4 transformation;
    VertexBuffer *vertexBuffer;
    GLuint vertexbuffer;


public:
    unsigned int identifier;

    virtual ~Renderable() {}
    virtual void render() {}
    virtual void load() {}
    virtual void unload() {}

    virtual VertexBuffer* getVertexBuffer() { return vertexBuffer; }


    glm::mat4 getTransformation();
    void setPosition(glm::vec3  position);
};


#endif /* defined(__Agile__Renderable__) */
