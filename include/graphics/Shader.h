#ifndef SHADER_HPP
#define SHADER_HPP
#include <GL/glew.h>

class ShaderProgram {

    void compileShaders(char* vertexProgram, char* fragmentProgram);
public:
    ShaderProgram();
    ~ShaderProgram();
    bool load(const char* vertexFilePath, const char* fragmentFilePath);

    GLuint id;
};

#endif
