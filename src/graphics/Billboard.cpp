//
// Created by Taha Doğan Güneş on 09/05/15.
//

#include "graphics/Billboard.h"
#include <graphics/VertexBuffer.h>
#include <graphics/Shader.h>

void Billboard::load(std::string fileName) {

}

Billboard::Billboard() {

    shaderProgram = new ShaderProgram();
    shaderProgram->load("./shaders/cubevertex.glsl", "./shaders/cubefragment.glsl");

    vbo = VertexBuffer::createCube();
}

Billboard::~Billboard() {

}

void Billboard::draw(Camera *camera) {

}
