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
#include "Position.h"

// Include GLEW



class Cube: public Renderable {

private:
    Position position;
    float length;
    



public:
    Cube (Position position, float length);
    
    void render ();
    void load   ();
    void unload();
    
    Position getPosition();
    float getLength();
    
    void setPosition(Position position);
    void setLength(float length);
    
    
};

#endif /* defined(__Agile__Cube__) */
