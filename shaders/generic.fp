#version 330 core


uniform vec3 Color;

in vec4 light_eyespace;
in vec4 position_eyespace;
in vec3 lightDir;
in vec2 UV;
in vec3 halfDir;



uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform vec3 ambient;
uniform vec3 specular;
uniform vec3 diffuse;
uniform float shininess;
uniform float dissolve;

out vec4 color;

void main() {

    float distanceToLight = length(light_eyespace - position_eyespace);
    float attenuation = 1.0 / (1.0 + 0.001 * pow(distanceToLight, 2));


    vec3 n = normalize(texture(normalTex, UV.st).rgb * 2.0 - 1.0);
    vec3 l = normalize(lightDir);
    vec3 h = normalize(halfDir);

    float nDotL = max(0.0, dot(n, l));
    float nDotH = max(0.0, dot(n, h));
    float power = (nDotL == 0.0) ? 0.0 : pow(nDotH, shininess*128.0);


    vec3 diff = diffuse * nDotL;
    vec3 spec = specular * power;
    vec3 col = ambient + diff + spec;
        
    color = vec4(attenuation * col * texture(diffuseTex, UV.st).rgb, 1.0);

    color.a = dissolve;
}