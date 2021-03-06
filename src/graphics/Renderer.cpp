#include <graphics/Mesh.h>
#include "graphics/Shader.h"
#include "world/Scene.h"
#include "graphics/VertexBuffer.h"
#include "graphics/Renderer.h"
#include "graphics/Renderable.h"
#include "resource/ObjLoader.h"
#include "world/Camera.h"
#include <graphics/SubMesh.h>
#include "world/Light.h"
#include <graphics/Material.h>
#include <sstream>


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
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    camera->perspective(70.0f, 4.0f/3.0f, 0.1f, 100.0f);


    glBindVertexArray(vaoid);


    glm::mat4 MVP;
    glm::mat4 modelViewMatrix;
    glm::mat3 normalMatrix;

    for (auto& renderable: renderList) {
		glm::mat4 model = renderable->getTransformation();

        MVP = camera->projection * (camera->view * model);
		modelViewMatrix = camera->view * model;
        normalMatrix = glm::inverse(glm::transpose(glm::mat3(modelViewMatrix)));

        for (auto submesh : renderable->mesh->subMeshes) {
            Material* mat = submesh->getMaterial();
            ShaderProgram* program = mat->program;



            glUseProgram(mat->program->id);
            mat->beginRendering();


			program->setUniform("cameraPosition", camera->position);

            int i = 0;
            program->setUniform("numLights", (int)lightList.size());
            for(auto light: lightList) {
                std::ostringstream ss;
                ss << "allLights[" << i << "].";
                std::string lightString = ss.str();
                glm::vec3 pos = light->getPosition();
                program->setUniform(lightString + std::string("position"), glm::vec4(pos.x, pos.y, pos.z, (light->type == LIGHT_DIRECTIONAL) ? 0.0f: 1.0f));
                program->setUniform(lightString + std::string("intensities"), light->intensities);
                program->setUniform(lightString + std::string("attenuation"), light->attenuation);
                program->setUniform(lightString + std::string("coneAngle"), light->coneAngle);
                program->setUniform(lightString + std::string("coneDirection"), light->coneDirection);
                program->setUniform(lightString + std::string("ambientCoefficient"), light->ambientCoefficient);
                ++i;
            }


            program->setUniform("MVP", MVP);
            program->setUniform("NormalMatrix", normalMatrix);
            program->setUniform("ModelMatrix", renderable->getTransformation());
            program->setUniform("ModelViewMatrix", modelViewMatrix);
            program->setUniform("ViewMatrix", camera->view);


            program->setUniform("ambient", mat->ambient);
            program->setUniform("specular", mat->specular);
            program->setUniform("diffuse", mat->diffuse);
            program->setUniform("shininess", mat->shininess);
            program->setUniform("dissolve", mat->dissolve);



            program->setUniform("diffuseTex", 0);
            program->setUniform("normalTex", 1);
            program->setUniform("specularTex", 2);

            if(renderable->mesh->getSkeleton()) {
                program->setUniform("Bones", renderable->boneMatrix);
            }




            /*glUniformMatrix4fv(glGetUniformLocation(generalShader->id, "MVP"), 1, GL_FALSE, &MVP[0][0]);
            glUniformMatrix3fv(glGetUniformLocation(generalShader->id, "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(generalShader->id, "ModelMatrix"), 1, GL_FALSE, &renderable->getTransformation()[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(generalShader->id, "ModelViewMatrix"), 1, GL_FALSE, &modelViewMatrix[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(generalShader->id, "ViewMatrix"), 1, GL_FALSE, &camera->view[0][0]);*/
            //glUniform3fv(glGetUniformLocation(generalShader->id, "Color"), 1, &renderable->getColor()[0]);

            submesh->getVertexBuffer()->bind();
            submesh->getVertexBuffer()->drawIndexed(submesh->triangleCount*3, submesh->indexOffset);
            submesh->getVertexBuffer()->unbind();
        }
    }



}


Renderer::~Renderer() {

}


void Renderer::updateRenderList(World *world, Camera *camera, float dt) {
    renderList.clear();
    lightList.clear();

    for (Renderable* renderable: world->getRenderables()) {
        renderList.push_back(renderable);
    }

    for (Light *light: world->getLights()) {
        lightList.push_back(light);
    }
}
