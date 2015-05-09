#version 330 core


uniform vec3 Color;
uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

in vec4 fragVert;
in vec2 UV;
in mat3 TBN;
in vec3 viewDir;


uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform sampler2D specularTex;
uniform vec3 ambient;
uniform vec3 specular;
uniform vec3 diffuse;
uniform float shininess;
uniform float dissolve;
uniform vec3 cameraPosition;


#define MAX_LIGHTS 10
uniform int numLights;
uniform struct Light {
   vec4 position;
   vec3 intensities; //a.k.a the color of the light
   float attenuation;
   float ambientCoefficient;
   float coneAngle;
   vec3 coneDirection;
} allLights[MAX_LIGHTS];


out vec4 color;

vec3 ApplyLight(Light light, vec3 surfaceColor, vec3 normal, vec3 surfacePos, vec3 surfaceToCamera) {
    vec3 surfaceToLight;
	vec4 lightPos = ViewMatrix * light.position;
	vec3 coneDir = normalize(TBN * (ViewMatrix * vec4(normalize(light.coneDirection), 0.0)).xyz);
    float attenuation = 1.0;
    if(light.position.w == 0.0) {
        //directional light
        surfaceToLight = normalize(TBN * (ViewMatrix * vec4(normalize(-light.position.xyz), 0.0)).xyz);
        attenuation = 1.0; //no attenuation for directional lights
    } else {
        //point light
        surfaceToLight = normalize(TBN * normalize(lightPos.xyz - surfacePos));
        float distanceToLight = length(lightPos.xyz - surfacePos);
        attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));

        //cone restrictions (affects attenuation)
        float lightToSurfaceAngle = degrees(acos(dot(-surfaceToLight, normalize(coneDir))));
        if(lightToSurfaceAngle > light.coneAngle){
            attenuation = 0.0;
        }
    }

    //ambient
    vec3 finalAmbient = light.ambientCoefficient * surfaceColor.rgb * light.intensities;

    //diffuse
    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    vec3 finalDiffuse = diffuseCoefficient * surfaceColor.rgb * light.intensities;
    
    //specular
    float specularCoefficient = 0.0;
    if(diffuseCoefficient > 0.0)
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), shininess);
    vec3 finalSpecular = specularCoefficient * texture(specularTex, UV.st).rgb * light.intensities;

    //linear color (color before gamma correction)
    return finalAmbient + attenuation*(finalDiffuse + finalSpecular);
}

void main() {

	vec3 normal = normalize(texture(normalTex, UV.st).rgb * 2.0 - 1.0);
    vec3 surfacePos = vec3(ModelViewMatrix * vec4(fragVert.xyz, 1));
    vec4 surfaceColor = texture(diffuseTex, UV.st);
    vec3 surfaceToCamera =  TBN * -surfacePos;
	
	
    vec3 linearColor = vec3(0);
	for(int i = 0; i < numLights; ++i){
        linearColor += ApplyLight(allLights[i], surfaceColor.rgb, normal, surfacePos, normalize(surfaceToCamera));
    }
	
     
    vec3 gamma = vec3(1.0/2.2);
    color = vec4(pow(linearColor, gamma), dissolve);



}