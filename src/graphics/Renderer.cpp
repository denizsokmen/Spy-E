#include <graphics/Mesh.h>
#include "graphics/Shader.h"
#include "world/Scene.h"
#include "graphics/VertexBuffer.h"
#include "graphics/Renderer.h"
#include "graphics/Renderable.h"
#include "resource/ObjLoader.h"
#include "world/Camera.h"
#include <graphics/SubMesh.h>
#include <graphics/Material.h>

Renderer::Renderer() {
	glGenVertexArrays(1, &vaoid);
	glBindVertexArray(vaoid);

    this->loadGeneralShader();

    objLoader = new ObjLoader();
}

void Renderer::loadGeneralShader() {
    generalShader = new ShaderProgram();
    generalShader->load("./shaders/vertex.glsl", "./shaders/fragment.glsl");
    //generalBuffer = objLoader->loadOBJ("./models/camera/camera-bottom.obj");


	
}

void Renderer::render(Camera* camera) {

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.2f, 0.0f);
    glUseProgram(generalShader->id);
    camera->perspective(70.0f, 4.0f/3.0f, 0.1f, 100.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    glm::mat4 MVP;
    glm::mat4 modelViewMatrix;
    glm::mat3 normalMatrix;

    for (auto& renderable: renderList) {

        MVP = camera->projection * (camera->view * renderable->getTransformation());
        modelViewMatrix = camera->view * renderable->getTransformation();
        normalMatrix = glm::inverse(glm::transpose(glm::mat3(modelViewMatrix)));

        for (auto submesh : renderable->mesh->subMeshes) {
            Material* mat = submesh->getMaterial();
            glUseProgram(mat->program->id);


            glUniformMatrix4fv(glGetUniformLocation(generalShader->id, "MVP"), 1, GL_FALSE, &MVP[0][0]);
            glUniformMatrix3fv(glGetUniformLocation(generalShader->id, "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(generalShader->id, "ModelMatrix"), 1, GL_FALSE, &renderable->getTransformation()[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(generalShader->id, "ModelViewMatrix"), 1, GL_FALSE, &modelViewMatrix[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(generalShader->id, "ViewMatrix"), 1, GL_FALSE, &camera->view[0][0]);
            glUniform3fv(glGetUniformLocation(generalShader->id, "Color"), 1, &renderable->color[0]);

            submesh->getVertexBuffer()->bind();
            submesh->getVertexBuffer()->draw();
            submesh->getVertexBuffer()->unbind();
        }
    }



}


Renderer::~Renderer() {

}


void Renderer::updateRenderList(World *world, Camera *camera, float dt) {
    renderList.clear();

    for (Renderable* renderable: world->getRenderables()) {
        renderList.push_back(renderable);
    }
}
