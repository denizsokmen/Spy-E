#version 330 core


uniform vec3 Color;

in vec4 light_eyespace;
in vec4 light2_eyespace;
in vec4 position_eyespace;
in vec3 normal_eyespace;
in vec2 UV;



uniform sampler2D diffuseTex;
uniform sampler2D normalTex;

out vec3 color;

void main() {

    float distanceToLight = length(light_eyespace - position_eyespace);
    float attenuation = 1.0 / (1.0 + 0.001 * pow(distanceToLight, 2));

    vec4 col = texture(diffuseTex, UV.xy);
    vec3 sumcol = vec3(0.0, 0.0, 0.0);
    vec3 l = normalize((light_eyespace-position_eyespace).xyz);
	float cosTheta = clamp( dot( normal_eyespace, l), 0.0, 1 );
    sumcol += attenuation * vec3(col) * vec3(1.0, 1.0, 1.0) * cosTheta;


   /* distanceToLight = length(light2_eyespace - position_eyespace);
    attenuation = 1.0 / (1.0 + 0.001 * pow(distanceToLight, 2));

    l = normalize((light2_eyespace-position_eyespace).xyz);
	cosTheta = clamp( dot( normal_eyespace, l), 0.0, 1 );
    sumcol += attenuation * cosTheta * (vec3(1.0, 0.0, 0.1));*/

    color =  sumcol + vec3(0.1, 0.1, 0.1);


}