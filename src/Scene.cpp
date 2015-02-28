
#include <Scene.h>
#include <Renderer.h>
#include "Camera.h"

#include <iostream>

void Scene::render() {
    renderer->render(camera);
}

void Scene::update() {

}

Scene::Scene() {
    renderer = new Renderer();
    camera = new Camera();
    camera->perspective(20.0f, 4.0f/3.0f, 0.1f, 100.0f);
    std::cout << "Scene initilization" << std::endl;
}