#version 330 core

layout(location = 0) in vec4 vertexPosition_modelspace;
layout(location = 1) in vec3 normal;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vertexPosition_modelspace;
}