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
	textures.resize(TEXTURE_LAST);
}

Material::~Material() {

}
