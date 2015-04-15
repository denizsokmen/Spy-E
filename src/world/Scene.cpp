
#include <world/Scene.h>
#include <graphics/Renderer.h>
#include "world/Camera.h"
#include "world/World.h"
#include "graphics/Renderable.h"

#include <iostream>


Scene::~Scene() {

}

Scene::Scene() {
    renderer = new Renderer();
    camera = new Camera();
    camera->perspective(20.0f, 4.0f/3.0f, 0.1f, 100.0f);
    camera->position = glm::vec3(0.0f, 10.0f, -10.0f);
    world = new World();
    std::cout << "Scene initilization" << std::endl;
}

void Scene::update(float dt) {
   /* renderList.clear();

    for (Renderable* renderable: world->getRenderables()) {
        renderList.push_back(renderable);

    }*/
}

void Scene::updateRenderList(float dt) {
    renderer->updateRenderList(world, camera, dt);
    /*renderList.clear();

    for (Renderable* renderable: world->getRenderables()) {
        renderList.push_back(renderable);

    }*/
}

void Scene::draw() {
    renderer->render(camera);
}