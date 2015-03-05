

#ifndef __SpyE_Entity__
#define __SpyE_Entity___

#include "Renderable.h"
#include "Mesh.h"
#include <string>

class Mesh;

class Entity : public Renderable {



public:
    std::string name;
    Mesh* mesh;
    Entity();

    VertexBuffer* getVertexBuffer() { return mesh->getVertexBuffer(); }

};

#endif
