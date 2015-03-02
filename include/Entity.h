

#ifndef __SpyE_Entity__
#define __SpyE_Entitiy__

#include "Renderable.h"
#include "Mesh.h"

class Mesh;

class Entity : public Renderable {

public:
    Mesh* mesh;

    Entity();

    VertexBuffer* getVertexBuffer() { return mesh->getVertexBuffer(); }

};

#endif
