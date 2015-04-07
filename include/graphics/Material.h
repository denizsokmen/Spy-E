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


    void beginRendering();
    void endRendering();




};

#endif