//
// Created by deniz on 02/04/15.
//

#ifndef SPYE_SKYBOX_H
#define SPYE_SKYBOX_H

#include <string>
#include <GL/glew.h>

class Camera;
class ShaderProgram;
class VertexBuffer;

class Skybox {

    void load(std::string filename,GLuint type);

public:

    Skybox(std::string posx, std::string negx, std::string posy, std::string negy, std::string posz, std::string negz);
    ~Skybox();
    GLuint cubeMap;
    ShaderProgram *shaderProgram;

    void draw(Camera* camera);

    VertexBuffer *vbo;
};


#endif //SPYE_SKYBOX_H
