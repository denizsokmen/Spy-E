#version 330

layout(location = 0) in vec4 vertex;
out vec3 texCoord;
uniform mat4 MVP;
 
void main() {
    vec4 pos = MVP * vec4(vertex.xyz, 1.0);
    gl_Position = pos.xyzz;
    texCoord = vertex.xyz;
}
