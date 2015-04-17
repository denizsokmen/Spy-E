//
// Created by Deniz Sokmen on 17/03/15.
//

#include "graphics/Material.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include <GL/glew.h>
void Material::beginRendering() {
    
}

void Material::endRendering() {

}

Material::Material() {
	textures.reserve(TEXTURE_LAST);
	diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	specular = glm::vec3(1.0f, 1.0f, 1.0f);

	shininess = 128.0f;
	dissolve = 1.0f;
}

Material::~Material() {

}
