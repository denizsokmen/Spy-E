#ifndef VERTEXBUFFER_H_INC
#define VERTEXBUFFER_H_INC

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

enum VBO {
    vboPosition = 0,
    vboNormal,
    vboUV,
    vboColor,
    vboTangent,
    MAX_VBO
};


class VertexBuffer {
    GLuint vbo[MAX_VBO];
    GLuint vboind;
    std::vector<float> vertex[MAX_VBO];
    std::vector<unsigned int> indices;


public:
    VertexBuffer();
    ~VertexBuffer();

    std::vector<glm::vec3> vertexList;
    void addVertex(glm::vec3 position);
    void addUV(glm::vec2 uv);
    void addColor(glm::vec4& color);
    void addNormal(glm::vec3 normal);
    void addTangent(glm::vec3 tangent);
    void addIndex(unsigned int index);

    void upload();

    void bind();
    void draw();
    void unbind();

	static VertexBuffer* createQuad();
    static VertexBuffer* createCube();
};

#endif

