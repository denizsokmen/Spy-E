#version 330 core

layout(location = 0) in vec4 vertexPosition_modelspace;
layout(location = 1) in vec3 normal;


uniform mat4 MVP;
uniform mat3 NormalMatrix;
uniform mat4 ModelMatrix;
uniform vec3 Color;


out vec4 position_worldspace;
out vec3 normal_eyespace;
out vec3 fragment_color;

void main() {
    gl_Position = MVP * vertexPosition_modelspace;
    normal_eyespace = NormalMatrix * normal;
    position_worldspace = ModelMatrix * vertexPosition_modelspace;
    fragment_color = Color;
}