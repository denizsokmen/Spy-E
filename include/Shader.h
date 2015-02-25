#ifndef SHADER_HPP
#define SHADER_HPP
#include <GL/glew.h>

class ShaderProgram {
    GLuint id;

public:
    bool load(const char* vertexFilePath, const char* fragmentFilePath);
};

#endif
