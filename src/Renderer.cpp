#include <Shader.h>
#include "Renderer.h"

void Renderer::render() {


}

Renderer::Renderer() {
    program = new ShaderProgram;
    program->load("vertex.glsl", "fragment.glsl");

}
