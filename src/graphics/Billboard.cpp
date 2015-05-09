//
// Created by Taha Doğan Güneş on 09/05/15.
//

#include "graphics/Billboard.h"
#include <graphics/VertexBuffer.h>
#include <graphics/Shader.h>
#include <graphics/Texture.h>
#include "world/Camera.h"
#include <SDL_image.h>


#define NUM_ROWS 10
#define NUM_COLUMNS 10

void Billboard::load(std::string fileName) {

}

Billboard::Billboard(const std::string& textureFileName) {

    texture = new Texture();
    texture->createFromSDL(IMG_Load(textureFileName.c_str()));


    shaderProgram = new ShaderProgram();
    shaderProgram->initialise();
    shaderProgram->addShader(GL_VERTEX_SHADER, "./shaders/billboard.vs");
    shaderProgram->addShader(GL_GEOMETRY_SHADER, "./shaders/billboard.gs");
    shaderProgram->addShader(GL_FRAGMENT_SHADER, "./shaders/billboard.fs");

    shaderProgram->finish();

    vbo = VertexBuffer::createCube();


    vpLocation = shaderProgram->getUniformLocation("gVP");
    gCameraPos = shaderProgram->getUniformLocation("gCameraPos");
    colorMapLocation = shaderProgram->getUniformLocation("gColorMap");

    if (vpLocation == INVALID_UNIFORM_LOCATION ||
        gCameraPos == INVALID_UNIFORM_LOCATION ||
        colorMapLocation == INVALID_UNIFORM_LOCATION) {
        fprintf(stderr, "Unable to init billboard\n");
    }




}

void Billboard::setMVP(glm::mat4& MVP) {
    glUniformMatrix4fv(vpLocation, 1, GL_FALSE, &MVP[0][0]);
}

void Billboard::setCameraPosition(const glm::vec3& pos){
    glUniform3f(gCameraPos, pos.x, pos.y, pos.z);
}

void Billboard::setColorTextureUnit(unsigned int textureUnit){
    glUniform1i(colorMapLocation, textureUnit);
}

void Billboard::draw(Camera *camera) {
    glUseProgram(shaderProgram->id);
    glm::mat4 MVP = camera->projection * (camera->view * glm::scale(glm::mat4(1.0f),glm::vec3(500,500,500)));
    this->setMVP(MVP);
    this->setCameraPosition(camera->position);
    this->texture->bind(COLOR_TEXTURE_UNIT);



    vbo->bind();
    vbo->draw();
    vbo->unbind();

}

Billboard::~Billboard() {

}

