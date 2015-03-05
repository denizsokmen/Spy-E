#include <Shader.h>
#include <Scene.h>
#include <VertexBuffer.h>
#include "Renderer.h"
#include "Renderable.h"
#include "Objloader.h"
#include "Camera.h"


Renderer::Renderer() {
    this->loadGeneralShader();
    objLoader = new ObjLoader();
}

void Renderer::loadGeneralShader() {
    generalShader = new ShaderProgram();
    generalShader->load("./shaders/vertex.glsl", "./shaders/fragment.glsl");
    //generalBuffer = objLoader->loadOBJ("./models/camera/camera-bottom.obj");

    glGenVertexArrays(1, &vaoid);
    glBindVertexArray(vaoid);
}

void Renderer::render(Camera* camera, std::vector<Renderable*> renderList) {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.2f, 0.0f);
    glUseProgram(generalShader->id);
    camera->lookAt(glm::vec3(10.0f, 10.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    for (auto renderable: renderList) {
        glm::mat4 MVP = camera->projection * camera->view * renderable->getTransformation();

        printf("%f %f %f %f %f %f %f %f %f\n",
                renderable->getTransformation()[0][0],  renderable->getTransformation()[0][1],  renderable->getTransformation()[0][3],
                renderable->getTransformation()[1][0],  renderable->getTransformation()[1][1],  renderable->getTransformation()[1][3],
                renderable->getTransformation()[2][0],  renderable->getTransformation()[2][1],  renderable->getTransformation()[2][3] );

        glUniformMatrix4fv(glGetUniformLocation(generalShader->id, "MVP"), 1, GL_FALSE, &MVP[0][0]);
        renderable->getVertexBuffer()->bind();
        renderable->getVertexBuffer()->draw();
        renderable->getVertexBuffer()->unbind();
    }
    glUseProgram(0);



}


Renderer::~Renderer() {

}