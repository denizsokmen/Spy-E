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


class Renderable {

private:


    
protected:
    glm::vec3 position;
    GLuint vertexbuffer;


public:
    unsigned int identifier;

    virtual ~Renderable() {}
    virtual void render() {}
    virtual void load() {}
    virtual void unload() {}

    glm::vec3 getPosition();
    void setPosition(glm::vec3  position);
};


#endif /* defined(__Agile__Renderable__) */
