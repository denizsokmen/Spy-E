#include <stdio.h>
#include "graphics/VertexBuffer.h"


VertexBuffer::VertexBuffer() : mode(GL_TRIANGLES) {

}

VertexBuffer::~VertexBuffer() {

}

void VertexBuffer::addVertex(glm::vec3 position) {
    vertexList.push_back(position);
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

void VertexBuffer::addColor(glm::vec4& color) {
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


void VertexBuffer::addBitangent(glm::vec3 bitangent) {
    vertex[vboBitangent].push_back(bitangent.x);
    vertex[vboBitangent].push_back(bitangent.y);
    vertex[vboBitangent].push_back(bitangent.z);
}

void VertexBuffer::addBoneIndex(glm::vec4& ind) {
    vertex[vboBoneIndex].push_back(ind.x);
    vertex[vboBoneIndex].push_back(ind.y);
    vertex[vboBoneIndex].push_back(ind.z);
    vertex[vboBoneIndex].push_back(ind.w);
}

void VertexBuffer::addWeight(glm::vec4& ind) {
    vertex[vboWeight].push_back(ind.x);
    vertex[vboWeight].push_back(ind.y);
    vertex[vboWeight].push_back(ind.z);
    vertex[vboWeight].push_back(ind.w);
}



void VertexBuffer::addIndex(unsigned int index) {
    indices.push_back(index);
}

void VertexBuffer::upload() {
    glGenBuffers(8, vbo);

    printf("VBO %d - %d - %d\n", vertex[vboPosition].size(), vertex[vboNormal].size(), indices.size());
    if (vertex[vboPosition].size() > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboPosition]);
        glBufferData(GL_ARRAY_BUFFER, vertex[vboPosition].size() * sizeof(float), &vertex[vboPosition][0], GL_STATIC_DRAW);
    }


    if (vertex[vboNormal].size() > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboNormal]);
        glBufferData(GL_ARRAY_BUFFER, vertex[vboNormal].size() * sizeof(float), &vertex[vboNormal][0], GL_STATIC_DRAW);
    }


    if (vertex[vboColor].size() > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboColor]);
        glBufferData(GL_ARRAY_BUFFER, vertex[vboColor].size() * sizeof(float), &vertex[vboColor][0], GL_STATIC_DRAW);
    }


    if (vertex[vboUV].size() > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboUV]);
        glBufferData(GL_ARRAY_BUFFER, vertex[vboUV].size() * sizeof(float), &vertex[vboUV][0], GL_STATIC_DRAW);
    }


    if (vertex[vboTangent].size() > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboTangent]);
        glBufferData(GL_ARRAY_BUFFER, vertex[vboTangent].size() * sizeof(float), &vertex[vboTangent][0], GL_STATIC_DRAW);
    }

    if (vertex[vboBitangent].size() > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboBitangent]);
        glBufferData(GL_ARRAY_BUFFER, vertex[vboBitangent].size() * sizeof(float), &vertex[vboBitangent][0], GL_STATIC_DRAW);
    }

    if (vertex[vboBoneIndex].size() > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboBoneIndex]);
        glBufferData(GL_ARRAY_BUFFER, vertex[vboBoneIndex].size() * sizeof(float), &vertex[vboBoneIndex][0], GL_STATIC_DRAW);
    }

    if (vertex[vboWeight].size() > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboWeight]);
        glBufferData(GL_ARRAY_BUFFER, vertex[vboWeight].size() * sizeof(float), &vertex[vboWeight][0], GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &vboind);
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

    if (vertex[vboUV].size() > 0) {
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboUV]);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    }

    if (vertex[vboTangent].size() > 0) {
        glEnableVertexAttribArray(4);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboTangent]);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    }

    if (vertex[vboBitangent].size() > 0) {
        glEnableVertexAttribArray(5);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboBitangent]);
        glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    }

    if (vertex[vboBoneIndex].size() > 0) {
        glEnableVertexAttribArray(6);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboBoneIndex]);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    }

    if (vertex[vboWeight].size() > 0) {
        glEnableVertexAttribArray(7);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vboWeight]);
        glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    }



    if (indices.size() > 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboind);
    }



}

void VertexBuffer::draw() {
    if (indices.size() > 0)
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*) 0);
    else
        glDrawArrays(GL_TRIANGLES, 0, vertex[vboPosition].size() / 4);
}

void VertexBuffer::drawIndexed(int count, int offset) {
    if (indices.size() > 0)
        glDrawElements(GL_TRIANGLES, (count > 0) ? count : indices.size(), GL_UNSIGNED_INT, (void*) offset);
}

void VertexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(4);
    glDisableVertexAttribArray(5);
    glDisableVertexAttribArray(6);
    glDisableVertexAttribArray(7);
}

VertexBuffer *VertexBuffer::createQuad() {
    VertexBuffer *vbo = new VertexBuffer();


    GLfloat vertices[] = {0, 1.0, 0, // top left corner
                          1.0, 1.0, 0, // top right corner
                          1.0, 0, 0, // bottom right corner
                          0, 0, 0}; // bottom left corner

    GLfloat uvs[] = {
            0, 1,
            1, 1,
            1, 0,
            0, 0
    };

    GLubyte indices[] = {0,1,2, // first triangle (bottom left - top left - top right)
            0,2,3}; // second triangle (bottom left - top right - bottom right)

    for(int i = 0; i < 4; i++)
        vbo->addVertex(glm::vec3(vertices[i*3], vertices[(i*3)+1], vertices[(i*3)+2]));

    for(int i = 0; i < 4; i++)
        vbo->addUV(glm::vec2(uvs[i*2], uvs[(i*2)+1]));

    for(int i = 0; i < 6; i++)
        vbo->addIndex(indices[i]);
    vbo->upload();
    return vbo;
}

VertexBuffer *VertexBuffer::createCube() {
    VertexBuffer *vbo = new VertexBuffer();

    GLfloat skyboxVertices[] = {
            // Positions
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
    };


    for(int i = 0; i < 36; i++)
        vbo->addVertex(glm::vec3(skyboxVertices[i*3], skyboxVertices[(i*3)+1], skyboxVertices[(i*3)+2]));


    vbo->upload();

    return vbo;
}

GLenum VertexBuffer::getMode() {
    return mode;
}

void VertexBuffer::setMode(GLenum mod) {
    mode = mod;
}
