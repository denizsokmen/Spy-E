#ifndef SHADER_HPP
#define SHADER_HPP

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

class ShaderProgram {
    GLuint id;

public:
    bool load(const char* vertexFilePath, const char* fragmentFilePath);
};

#endif
