//
// Created by Taha Doğan Güneş on 09/05/15.
//

#ifndef SPYE_BILLBOARD_H
#define SPYE_BILLBOARD_H

#include <string>
#include <GL/glew.h>
#include <glm/detail/type_mat4x4.hpp>
#define COLOR_TEXTURE_UNIT GL_TEXTURE0
#define INVALID_VALUE 0xffffffff

class Camera;
class ShaderProgram;
class VertexBuffer;
class Texture;

class Billboard {
    void load(std::string fileName);

public:
    Billboard(const std::string& textureFileName);
    ~Billboard();
    ShaderProgram* shaderProgram;
    VertexBuffer* vbo;


    void draw(Camera* camera);


    GLint colorMapLocation;
    GLint gCameraPos;
    GLint vpLocation;



    void setCameraPosition(const glm::vec3 &pos);

    void setColorTextureUnit(unsigned int textureUnit);

    void setMVP(glm::mat4&  MVP);

    Texture *texture;
};

#endif //SPYE_BILLBOARD_H
