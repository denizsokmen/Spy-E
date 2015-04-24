
#include "graphics/Mesh.h"
#include "graphics/SubMesh.h"
#include "graphics/Skeleton.h"


Mesh::Mesh(): skeleton(NULL) {

}

Mesh::~Mesh() {

}

VertexBuffer *Mesh::getVertexBuffer() {
    if (subMeshes.size() > 0)
        return subMeshes[0]->getVertexBuffer();
    return vertexBuffer;
}

void Mesh::setSkeleton(Skeleton *skeleton) {
    this->skeleton = skeleton;

    boneMatrix.resize(skeleton->bones.size(), glm::mat4(1.0f));
}

Skeleton* Mesh::getSkeleton() {
    return skeleton;
}
