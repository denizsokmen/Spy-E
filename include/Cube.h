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
#include "Point.h"

// Include GLEW



class Cube: public Renderable {

private:
    Point point;
    float length;
    


    
public:
    Cube (Point point, float length);
    
    void render ();
    void load   ();
    void unload();
    
    Point getPoint();
    float getLength();
    
    void setPoint(Point point);
    void setLength(float length);
    
    
};

#endif /* defined(__Agile__Cube__) */
