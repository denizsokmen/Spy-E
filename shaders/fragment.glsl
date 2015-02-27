#version 330 core

//in vec3 fragmentColor;

out vec3 color;

void main() {
    color = vec3(gl_FragCoord.w, 0.0f, 0.0f);

}