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

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


Renderer::~Renderer() {

}