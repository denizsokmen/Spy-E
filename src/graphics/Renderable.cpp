//
//  Renderable.cpp
//  Spy-E
//
//  Created by Taha Doğan Güneş on 21/02/15.
//  Copyright (c) 2015 Spy-E. All rights reserved.
//

#include "graphics/Renderable.h"
#include "graphics/Mesh.h"

Renderable::Renderable() {
    position.x=0.0f;
    position.y=0.0f;
    position.z=0.0f;



}

VertexBuffer* Renderable::getVertexBuffer() {
    return mesh->getVertexBuffer();
}
