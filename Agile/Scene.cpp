//
//  Scene.cpp
//  Agile
//
//  Created by Taha Doğan Güneş on 17/02/15.
//  Copyright (c) 2015 CS476. All rights reserved.
//

#include "Scene.h"


Scene::Scene() {
    this->objects = new std::vector<Renderable *>;
}

void Scene::add(Renderable *object){
    this->objects->push_back(object);
    object->identifier = 1;

}


void Scene::load(){
    for (auto item = this->objects->begin(); item != this->objects->end(); ++item) {
        Renderable *renderableObject = *item;
        renderableObject->load();
    }
}
void Scene::render(){
    for (auto item = this->objects->begin(); item != this->objects->end(); ++item) {
        Renderable *renderableObject = *item;
        renderableObject->render();
    }
}

void Scene::unload(){
    for (auto item = this->objects->begin(); item != this->objects->end(); ++item) {
        Renderable *renderableObject = *item;
        renderableObject->unload();
    }
}
