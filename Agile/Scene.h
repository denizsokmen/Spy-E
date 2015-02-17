//
//  Scene.h
//  Agile
//
//  Created by Taha Doğan Güneş on 17/02/15.
//  Copyright (c) 2015 CS476. All rights reserved.
//

#ifndef __Agile__Scene__
#define __Agile__Scene__

#include <iostream>
#include <vector>

#include "Renderable.h"

class Scene {
    
private:
    std::vector<Renderable *> *objects;
    int count = 1;
    
    
public:
    Scene();
    
    void add(Renderable *object);
    
    
    void load();
    void render();
    void unload();
};

#endif /* defined(__Agile__Scene__) */
