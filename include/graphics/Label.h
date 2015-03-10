//
//  Label.h
//  Spy-E
//
//  Created by Taha Doğan Güneş on 23/02/15.
//  Copyright (c) 2015 Spy-E. All rights reserved.
//


#ifndef __SpyE__Label__
#define __SpyE__Label__

#include <stdio.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "Renderable.h"

class VertexBuffer;

class Label: public Renderable {

private:
    float length;
    std::string text;
    VertexBuffer* vertexBuffer;

public:
    Label (glm::vec3 position, std::string text);

};

#endif /* defined(__SpyE__Label__) */
