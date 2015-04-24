#include "graphics/SubMesh.h"
#include "graphics/Material.h"
#include "graphics/Mesh.h"

SubMesh::SubMesh() {
    material = NULL;
    vertexBuffer = NULL;
    triangleCount = 0;
}

SubMesh::~SubMesh() {

}

VertexBuffer *SubMesh::getVertexBuffer() {
    if (vertexBuffer != NULL)
        return vertexBuffer;
    return mesh->vertexBuffer;
}

void SubMesh::setVertexBuffer(VertexBuffer *vertexBuffer) {
    this->vertexBuffer = vertexBuffer;
}

Material *SubMesh::getMaterial() {
    if (material != NULL)
        return material;

    return mesh->material;
}

void SubMesh::setMaterial(Material *material) {
    this->material = material;
}

