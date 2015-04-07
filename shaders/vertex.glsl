#version 330 core

layout(location = 0) in vec4 vertexPosition_modelspace;
layout(location = 1) in vec3 normal;


uniform mat4 MVP;
uniform mat3 NormalMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelViewMatrix;



out vec4 position_eyespace;
out vec4 light_eyespace;
out vec3 normal_eyespace;


void main() {
    gl_Position = MVP * vertexPosition_modelspace;
    normal_eyespace = NormalMatrix * normal;
    position_eyespace = ModelViewMatrix * vertexPosition_modelspace;
    light_eyespace = ViewMatrix * vec4(10.0, 10.0,10.0, 1.0);

}