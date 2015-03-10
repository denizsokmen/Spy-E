#ifndef SHADER_HPP
#define SHADER_HPP
#include <GL/glew.h>

class ShaderProgram {

public:
    bool load(const char* vertexFilePath, const char* fragmentFilePath);
    GLuint id;
};

#endif
