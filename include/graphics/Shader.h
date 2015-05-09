#ifndef SHADER_HPP
#define SHADER_HPP
#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <list>
#define GLCheckError() (glGetError() == GL_NO_ERROR)

class ShaderProgram {


public:
    ShaderProgram();
    ~ShaderProgram();
    bool addShader(GLenum type, const char *filePath);
    bool load(const char* vertexFilePath, const char* fragmentFilePath);

    bool finalizeShaders();

    void setUniform(GLint location, const std::vector<glm::mat4>& value) const;
    void setUniform(GLint location, const glm::mat4& value) const;
    void setUniform(GLint location, const glm::mat3& value) const;
    void setUniform(GLint location, const glm::vec3& value) const;
    void setUniform(GLint location, const glm::vec4& value) const;
    void setUniform(GLint location, const float& value) const;
    void setUniform(GLint location, const GLint& value) const;

    template<typename T>
    void setUniform(const std::string& name, T&& value) const
    {
        GLint location = glGetUniformLocation(id, name.c_str());
        /*if(-1 == location)
        {
            std::string error = "Program::setUniform() -> could not get location of uniform " + name;
            printf("Warning %s\n", error.c_str());
        }*/
        setUniform(location, std::forward<T>(value));
    }


    GLuint id;
    typedef std::list<GLuint> ShaderObjectList;
    ShaderObjectList shaderObjList;

};

#endif
