#version 330 core

//in vec3 fragmentColor;


in vec4 position_worldspace;
in vec3 normal_eyespace;

out vec3 color;

void main() {
    vec3 l = normalize(vec3(0.0, 1.0, 1.0));
	float cosTheta = clamp( dot( normal_eyespace, l), 0,1 );
    color = vec3(1.0, 0.0, 0.0) * cosTheta;

}