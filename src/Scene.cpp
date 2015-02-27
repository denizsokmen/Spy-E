
#include <Scene.h>
#include <Renderer.h>


#include <iostream>

void Scene::render() {

}

Scene::Scene() {
    this->renderer = new Renderer();
    std::cout << "Scene initilization" << std::endl;
}
