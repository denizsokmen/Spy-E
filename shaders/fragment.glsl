#version 330 core




in vec4 position_worldspace;
in vec3 normal_eyespace;
in vec3 fragment_color;

out vec3 color;

void main() {
    vec3 l = normalize(vec3(0.0, 1.0, 9.0));
	float cosTheta = clamp( dot( normal_eyespace, l), 0.0, 1 );
    color = fragment_color * cosTheta;

}