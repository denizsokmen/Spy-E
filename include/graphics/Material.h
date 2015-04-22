#ifndef MATERIAL_H_INC
#define MATERIAL_H_INC

#include <glm/glm.hpp>
#include <vector>

class ShaderProgram;
class Texture;

enum TextureTypes {
	TEXTURE_DIFFUSE=0,
	TEXTURE_NORMAL,
	TEXTURE_LAST

};

class Material {


public:

    Material();
    ~Material();
    glm::vec4 color;
    ShaderProgram* program;


	std::vector<Texture*> textures;
    glm::vec3 diffuse;
    glm::vec3 ambient;
    glm::vec3 specular;

    float shininess;
    float dissolve;


    void beginRendering();
    void endRendering();

    void setTexture(TextureTypes type, Texture* texture);




};

#endif