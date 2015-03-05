//
//  Renderable.cpp
//  Spy-E
//
//  Created by Taha Doğan Güneş on 21/02/15.
//  Copyright (c) 2015 Spy-E. All rights reserved.
//

#include "Renderable.h"
#include "Mesh.h"

Renderable::Renderable() {
    position.x=1.0f;
    position.y=1.0f;
    position.z=1.0f;


}

VertexBuffer* Renderable::getVertexBuffer() {
    return mesh->getVertexBuffer();
}
