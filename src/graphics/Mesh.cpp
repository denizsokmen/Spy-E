#include "graphics/Mesh.h"
#include "graphics/SubMesh.h"


Mesh::Mesh(){
}

Mesh::~Mesh() {

}

VertexBuffer *Mesh::getVertexBuffer() {
    if (subMeshes.size() > 0)
        return subMeshes[0]->getVertexBuffer();
    return vertexBuffer;
}
