#include "graphics/Renderer.h"
#include "graphics/Shader.h"
#include "graphics/Renderable.h"
#include "graphics/Cube.h"


Cube::Cube() {

}

void Cube::render(Renderer *renderer) {
    Renderable::render(renderer);
    glUniform3fv(glGetUniformLocation(renderer->generalShader->id, "Color"), 1, &color[0]);
    printf("Set color %f, %f, %f \n", color[0], color[1], color[2]);
}



Cube::~Cube() {

}
