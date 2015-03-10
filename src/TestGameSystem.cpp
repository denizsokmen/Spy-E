#include "TestGameSystem.h"
#include "logic/Game.h"
#include "world/Scene.h"
#include "graphics/Mesh.h"
#include "graphics/Objloader.h"
#include "graphics/Renderable.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


TestGameSystem::TestGameSystem(Game *game) {

    Mesh* mesh = new Mesh();
    ObjLoader* objLoader = new ObjLoader();
    mesh->setVertexBuffer(objLoader->loadOBJ("./models/camera/camera-bottom.obj"));
    entity = game->scene->getWorld()->createRenderable();
    //glm::mat4 trans = glm::scale(entity->getTransformation(), glm::vec3(2.0f, 2.0f, 2.0f));

    entity->orientation = glm::rotate(entity->orientation, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    entity->mesh = mesh;
    //entity->setTransformation(trans);
}

void TestGameSystem::update(float dt) {
    //glm::mat4 trans = glm::translate(entity->getTransformation(), glm::vec3(dt, dt, dt));
    //glm::mat4 trans = glm::rotate(entity->getTransformation(), 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    entity->orientation = glm::rotate(entity->orientation, 90.0f * dt, glm::vec3(0.0f, 0.0f, 1.0f));
    entity->position += glm::vec3(0.000f, 0.00f, 0.00f);
   // entity->setTransformation(trans);
}

void TestGameSystem::draw() {

}