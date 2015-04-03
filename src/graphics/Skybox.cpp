//
// Created by deniz on 02/04/15.
//

#include <GL/glew.h>
#include <SDL_surface.h>
#include <SDL_image.h>
#include <graphics/Shader.h>
#include <glm/glm.hpp>
#include <graphics/VertexBuffer.h>
#include "world/Camera.h"
#include "graphics/Skybox.h"

Skybox::Skybox(std::string posx, std::string negx, std::string posy, std::string negy, std::string posz,
               std::string negz) {
    glGenTextures(1, &cubeMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);
    load(posx, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
    load(negx, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
    load(posy, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
    load(negy, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
    load(posz, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
    load(negz, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    shaderProgram = new ShaderProgram();
    shaderProgram->load("./shaders/cubevertex.glsl", "./shaders/cubefragment.glsl");

    vbo = VertexBuffer::createCube();
}

void Skybox::load(std::string filename, GLuint type) {
    GLenum mode = GL_RGB;
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface != NULL) {
        if (surface->format->BytesPerPixel == 4) {
            mode = GL_RGBA;
        }

        glTexImage2D(type, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
    }
    else {
        printf("Error loading: %s\n", filename.c_str());
    }
}

Skybox::~Skybox() {
    glDeleteTextures(1, &cubeMap);
}

void Skybox::draw(Camera *camera) {
    //glDepthMask(GL_FALSE);

    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);

    glUseProgram(shaderProgram->id);
    glm::mat4 MVP = camera->projection * (camera->view * glm::scale(glm::mat4(1.0f),glm::vec3(100,100,100)));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

    glUniform1i(glGetUniformLocation(shaderProgram->id, "cubemap"), 0);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram->id, "MVP"), 1, GL_FALSE, &MVP[0][0]);
    vbo->bind();
    vbo->draw();
    vbo->unbind();
    //glDepthMask(GL_TRUE);

    glCullFace(GL_BACK);
}