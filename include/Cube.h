//
//  Cube.h
//  Agile
//
//  Created by Taha Doğan Güneş on 17/02/15.
//  Copyright (c) 2015 CS476. All rights reserved.
//

#ifndef __Agile__Cube__
#define __Agile__Cube__

#include <stdio.h>

#include "Renderable.h"


// Include GLEW



class Cube: public Renderable {

private:
    float length;



public:
    Cube (glm::vec3 position, float length);
    
    void render ();
    void load   ();
    void unload();
    


    float getLength();
    void setLength(float length);
    
    
};

#endif /* defined(__Agile__Cube__) */
