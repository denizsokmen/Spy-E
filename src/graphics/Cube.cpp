#include "graphics/Renderer.h"
#include "graphics/Shader.h"
#include "graphics/Renderable.h"
#include "graphics/Cube.h"


Cube::Cube() {

}

void Cube::render(Renderer *renderer) {
    Renderable::render(renderer);
    glUniform3fv(glGetUniformLocation(renderer->generalShader->id, "Color"), 1, &color[0]);
}



Cube::~Cube() {

}
