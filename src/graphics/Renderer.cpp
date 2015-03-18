#include "graphics/Shader.h"
#include "world/Scene.h"
#include "graphics/VertexBuffer.h"
#include "graphics/Renderer.h"
#include "graphics/Renderable.h"
#include "graphics/ObjLoader.h"
#include "world/Camera.h"


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

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.2f, 0.0f);
    glUseProgram(generalShader->id);
    camera->perspective(70.0f, 4.0f/3.0f, 0.1f, 100.0f);
    camera->lookAt(camera->position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    for (auto renderable: renderList) {
        glm::mat4 MVP = camera->projection * (camera->view * renderable->getTransformation());
        glm::mat3 normalMatrix = glm::mat3(camera->view * renderable->getTransformation());

        glUniformMatrix4fv(glGetUniformLocation(generalShader->id, "MVP"), 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix3fv(glGetUniformLocation(generalShader->id, "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(generalShader->id, "ModelMatrix"), 1, GL_FALSE, &renderable->getTransformation()[0][0]);
        renderable->getVertexBuffer()->bind();
        renderable->getVertexBuffer()->draw();
        renderable->getVertexBuffer()->unbind();
    }
    glUseProgram(0);



}


Renderer::~Renderer() {

}