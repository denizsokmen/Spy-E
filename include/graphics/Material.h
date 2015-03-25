#ifndef MATERIAL_H_INC
#define MATERIAL_H_INC

#include <glm/glm.hpp>


class ShaderProgram;
class Texture;

class Material {


public:

    Material();
    ~Material();
    glm::vec4 color;
    ShaderProgram* program;

    Texture* diffuseTexture;
    Texture* normalTexture;


    void beginRendering();
    void endRendering();




};

#endif