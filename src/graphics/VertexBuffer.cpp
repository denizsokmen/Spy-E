#include "graphics/VertexBuffer.h"


VertexBuffer::VertexBuffer() {

}

VertexBuffer::~VertexBuffer() {

}

void VertexBuffer::addVertex(glm::vec3 position) {
    vertex[vboPosition].push_back(position.x);
    vertex[vboPosition].push_back(position.y);
    vertex[vboPosition].push_back(position.z);
    vertex[vboPosition].push_back(1.0f);
}

void VertexBuffer::addNormal(glm::vec3 normal) {
    vertex[vboNormal].push_back(normal.x);
    vertex[vboNormal].push_back(normal.y);
    vertex[vboNormal].push_back(normal.z);
}

void VertexBuffer::addUV(glm::vec2 uv) {
    vertex[vboUV].push_back(uv.x);
    vertex[vboUV].push_back(uv.y);
}

void VertexBuffer::addColor(glm::vec4 color) {
    vertex[vboColor].push_back(color.r);
    vertex[vboColor].push_back(color.g);
    vertex[vboColor].push_back(color.b);
    vertex[vboColor].push_back(color.a);
}

void VertexBuffer::addTangent(glm::vec3 tangent) {
    vertex[vboTangent].push_back(tangent.x);
    vertex[vboTangent].push_back(tangent.y);
    vertex[vboTangent].push_back(tangent.z);
}

void VertexBuffer::addIndex(unsigned int index) {
    indices.push_back(index);
}

void VertexBuffer::upload() {
    glGenBuffers(5, vbo);

    printf("VBO %d - %d\n", vertex[vboPosition].size(), vertex[vboNormal].size());
    if (vertex[vboPosition].size() > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboPosition]);
        glBufferData(GL_ARRAY_BUFFER, vertex[vboPosition].size() * sizeof(glm::vec4), &vertex[vboPosition][0], GL_STATIC_DRAW);
    }


    if (vertex[vboNormal].size() > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboNormal]);
        glBufferData(GL_ARRAY_BUFFER, vertex[vboNormal].size() * sizeof(glm::vec3), &vertex[vboNormal][0], GL_STATIC_DRAW);
    }


    if (vertex[vboColor].size() > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboColor]);
        glBufferData(GL_ARRAY_BUFFER, vertex[vboColor].size() * sizeof(glm::vec4), &vertex[vboColor][0], GL_STATIC_DRAW);
    }


    if (vertex[vboUV].size() > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboUV]);
        glBufferData(GL_ARRAY_BUFFER, vertex[vboUV].size() * sizeof(glm::vec2), &vertex[vboUV][0], GL_STATIC_DRAW);
    }


    if (vertex[vboTangent].size() > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboTangent]);
        glBufferData(GL_ARRAY_BUFFER, vertex[vboTangent].size() * sizeof(glm::vec3), &vertex[vboTangent][0], GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    if (indices.size() > 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboind);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }
    printf("Success \n");
}

void VertexBuffer::bind() {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[vboPosition]);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[vboNormal]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);



}

void VertexBuffer::draw() {
    glDrawArrays(GL_TRIANGLES, 0, vertex[vboPosition].size() / 4);
}

void VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
