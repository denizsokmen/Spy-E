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

Renderable::~Renderable() {

}

void Renderable::render(Renderer *renderer) {
    VertexBuffer *vertexBuffer = mesh->getVertexBuffer();
    vertexBuffer->bind();
    vertexBuffer->draw();
    vertexBuffer->unbind();
}
