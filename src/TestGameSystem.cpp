#include "TestGameSystem.h"
#include "Entity.h"
#include "Game.h"
#include "Scene.h"
#include "Mesh.h"
#include "Objloader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


TestGameSystem::TestGameSystem(Game *game) {

    Mesh* mesh = new Mesh();
    ObjLoader* objLoader = new ObjLoader();
    mesh->setVertexBuffer(objLoader->loadOBJ("./models/camera/camera-bottom.obj"));
    entity = game->scene->getWorld()->createEntity();
    entity->mesh = mesh;
}

void TestGameSystem::update(float dt) {
    //glm::mat4 trans = glm::translate(entity->getTransformation(), glm::vec3(1.0f, 1.0f, 1.0f));
    //entity->setTransformation(trans);
}

void TestGameSystem::draw() {

}