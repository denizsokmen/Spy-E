#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "graphics/Shader.h"
#include "utils/FileOperations.h"

ShaderProgram::ShaderProgram() {
    id = 0;
}


bool ShaderProgram::addShader(GLenum type, const char* filePath) {
    std::string s;

    if (!FileOperations::readFile(filePath, s)) {
        return false;
    }
    GLuint shaderObject = glCreateShader(type);

    if (shaderObject == 0) {
        fprintf(stderr, "Error creating shader type %d\n", type);
        return false;
    }

    shaderObjList.push_back(shaderObject);

    const GLchar* p[1];
    p[0] = s.c_str();
    GLint lengths[1] = { (GLint)s.size() };

    glShaderSource(shaderObject, 1, p, lengths);
    glCompileShader(shaderObject);
    GLint success;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderObject, 1024, NULL, infoLog);
        fprintf(stderr, "Error compiling '%s': '%s'\n", filePath, infoLog);
        return false;
    }

    glAttachShader(id, shaderObject);

    return true;
}

bool ShaderProgram::finalizeShaders() {
    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(id, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        return false;
    }

    glValidateProgram(id);
    glGetProgramiv(id, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(id, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);

    }

    // Delete the intermediate shader objects that have been added to the program
    for (ShaderObjectList::iterator it = shaderObjList.begin() ; it != shaderObjList.end() ; it++) {
        glDeleteShader(*it);
    }

    shaderObjList.clear();

    return GLCheckError();
}

bool ShaderProgram::load(const char *vertexFilePath, const char *fragmentFilePath) {

    this->initialise();
    this->addShader(GL_VERTEX_SHADER, vertexFilePath);
    this->addShader(GL_FRAGMENT_SHADER, fragmentFilePath);
    this->finish();


}
bool ShaderProgram::initialise() {
    id = glCreateProgram();
    if (id == 0) {
        fprintf(stderr, "Error creating shader program\n");
        return false;
    }
}

void ShaderProgram::finish(){
    this->finalizeShaders();
    glUseProgram(id);
}


ShaderProgram::~ShaderProgram() {
    for (ShaderObjectList::iterator it = shaderObjList.begin() ; it != shaderObjList.end() ; it++) {
        glDeleteShader(*it);
    }

    if (id != 0) {
        glDeleteProgram(id);
        id = 0;
    }
}

GLint ShaderProgram::getUniformLocation(const char* uniformName){
    GLint location = glGetUniformLocation(this->id, uniformName);

    if (location == INVALID_UNIFORM_LOCATION) {
        fprintf(stderr, "Warning! Unable to get the location of uniform '%s'\n", uniformName);
    }
    return location;
}

void ShaderProgram::setUniform(GLint location, glm::mat4 const &value) const {
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}


void ShaderProgram::setUniform(GLint location, glm::mat3 const &value) const {
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniform(GLint location, const glm::vec3 &value) const {
	glUniform3fv(location, 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform(GLint location, const glm::vec4 &value) const {
	glUniform4fv(location, 1, glm::value_ptr(value));

}

void ShaderProgram::setUniform(GLint location, const float &value) const {
	glUniform1f(location, value);
}

void ShaderProgram::setUniform(GLint location, const GLint &value) const {
	glUniform1i(location, value);
}

void ShaderProgram::setUniform(GLint location, const std::vector<glm::mat4> &value) const {
	glUniformMatrix4fv(location, value.size(), GL_FALSE, glm::value_ptr(value[0]));
}
