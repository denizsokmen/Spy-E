//
// Created by deniz on 27/03/15.
//
#include <input/KeyboardButtonHandler.h>
#include <input/MouseButtonHandler.h>
#include "SpyE.h"
#include <logic/Game.h>
#include <stdio.h>
#include <world/Scene.h>
#include <glm/glm.hpp>
#include <graphics/Renderable.h>
#include <graphics/Shader.h>
#include <graphics/VertexBuffer.h>
#include <world/WorldLoader.h>
#include <world/Camera.h>
#include <graphics/ui/Menu.h>
#include <graphics/Skybox.h>
#include <resource/ResourceManager.h>

SpyE::SpyE(Game *game) {
    this->game = game;
	active = false;
}

void SpyE::init() {
	
}

void SpyE::activate() {
    active=true;

	generalShader = new ShaderProgram();
	generalShader->load("./shaders/quad_vertex.glsl", "./shaders/quad_fragment.glsl");
	vbo = VertexBuffer::createQuad();




	
	entity = game->scene->getWorld()->createRenderable("box");
	entity->setPosition(glm::vec3(0, 2.0f, 0));
	entity->setColor(glm::vec3(0, 0, 1.0f));
	//entity->setScale(glm::vec3(0.1f, 0.1f, 0.1f));
    entity->mesh = ResourceManager::instance()->createSkeletalMesh("./assets/entities/hellknight/hellknight.md5mesh").get();

    entity->addAnimation("lurking", "./assets/entities/hellknight/idle.md5mesh");
    entity->setAnimation("lurking");

	WorldLoader loader(game->scene->getWorld());
	loader.load("./worlds/level1/");

	skybox = new Skybox("./assets/texture/skybox/vr.jpg", "./assets/texture/skybox/vr.jpg",
		"./assets/texture/skybox/vr.jpg", "./assets/texture/skybox/vr.jpg",
		"./assets/texture/skybox/vr.jpg", "./assets/texture/skybox/vr.jpg");


}

void SpyE::update(float dt) {
    if (!active)
        return;

	Entity* weapon = this->game->scene->getWorld()->getEntity("weapon002");
	weapon->setOrientation(glm::rotate(weapon->getOrientation(), 0.5f * dt, glm::vec3(0.0f, 1.0f, 0.0f)));


    game->scene->camera->position = glm::vec3(entity->getPosition().x, entity->getPosition().y+10.0f, entity->getPosition().z + 20.0f);
    game->scene->camera->lookAt(game->scene->camera->position, entity->getPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
    game->scene->camera->focus = entity->getPosition();

    if (game->input->justPressed("Left Click"))
        printf("clicked\n");

}


void SpyE::draw() {
	if (!active)
		return;

	skybox->draw(game->scene->camera);
}