
#include <Scene.h>
#include <Renderer.h>
#include "Camera.h"
#include "World.h"
#include "Renderable.h"

#include <iostream>

void Scene::draw() {
    renderer->render(camera, renderList);
}

Scene::~Scene() {

}

Scene::Scene() {
    renderer = new Renderer();
    camera = new Camera();
    camera->perspective(70.0f, 4.0f/3.0f, 0.1f, 100.0f);
    world = new World();
    std::cout << "Scene initilization" << std::endl;
}

void Scene::update(float dt) {
    renderList.clear();

    for (Renderable* renderable: world->getRenderables()) {
        renderList.push_back(renderable);

    }
}
