#include <Shader.h>
#include "Renderer.h"

void Renderer::render() {


}

Renderer::Renderer() {
    generalShader = new ShaderProgram;
	generalShader->load("vertex.glsl", "fragment.glsl");

}
