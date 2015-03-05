#include "TestGameSystem.h"
#include "Game.h"
#include "Scene.h"
#include "Mesh.h"
#include "Objloader.h"
#include "Renderable.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


TestGameSystem::TestGameSystem(Game *game) {

    Mesh* mesh = new Mesh();
    ObjLoader* objLoader = new ObjLoader();
    mesh->setVertexBuffer(objLoader->loadOBJ("./models/camera/camera-bottom.obj"));
    entity = game->scene->getWorld()->createRenderable();
    glm::mat4 trans = glm::scale(entity->getTransformation(), glm::vec3(2.0f, 2.0f, 2.0f));

    entity->mesh = mesh;
    entity->setTransformation(trans);
}

void TestGameSystem::update(float dt) {
    //glm::mat4 trans = glm::translate(entity->getTransformation(), glm::vec3(dt, dt, dt));
    glm::mat4 trans = glm::rotate(entity->getTransformation(), 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    entity->setTransformation(trans);
}

void TestGameSystem::draw() {

}