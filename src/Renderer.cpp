#include <Shader.h>
#include <Scene.h>
#include "Renderer.h"


Renderer::Renderer() {
    this->loadGeneralShader();
}

void Renderer::loadGeneralShader() {
    generalShader = new ShaderProgram;
    generalShader->load("./shaders/vertex.glsl", "./shaders/fragment.glsl");
}

void Renderer::render() {

}


Renderer::~Renderer() {

}