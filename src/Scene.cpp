
#include <Scene.h>
#include <Renderer.h>


#include <iostream>

void Scene::render() {
    this->renderer->render();
}

void Scene::update() {

}

Scene::Scene() {
    this->renderer = new Renderer();
    std::cout << "Scene initilization" << std::endl;
}
