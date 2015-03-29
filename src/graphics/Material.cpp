//
// Created by Deniz Sokmen on 17/03/15.
//

#include "graphics/Material.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include <GL/glew.h>
void Material::beginRendering() {
    if (program != NULL) {
		glUseProgram(program->id);
		diffuseTexture->bind(0);
    }
}

void Material::endRendering() {

}

Material::Material() {

}

Material::~Material() {

}
