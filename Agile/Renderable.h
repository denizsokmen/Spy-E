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

class Renderable {

public:
    unsigned int identifier;
    
protected:
    GLuint vertexbuffer;


public:
    virtual ~Renderable() {}
    virtual void render() {}
    virtual void load() {}
    virtual void unload() {}
};


#endif /* defined(__Agile__Renderable__) */
