//
// Created by Deniz Sokmen on 17/03/15.
//

#include "graphics/Material.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include <GL/glew.h>
#include <resource/ResourceManager.h>

void Material::beginRendering() {
	GLuint bind = 0;
    for(auto tex: textures) {
		tex->bind(bind);
		bind++;
	}
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

	textures.push_back(ResourceManager::instance()->createTexture("./assets/texture/identitydiffuse.png").get());
	textures.push_back(ResourceManager::instance()->createTexture("./assets/texture/identitynormal.png").get());
}

Material::~Material() {

}

void Material::setTexture(TextureTypes type, Texture *texture) {
	if (texture == NULL)
		return;

	if (type < TEXTURE_LAST)
		textures[type] = texture;

}
