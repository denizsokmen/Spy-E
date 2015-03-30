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

SpyE::SpyE(Game *game) {
    this->game = game;
}

void SpyE::init() {

}

void SpyE::activate() {
    active=true;
    entity = game->scene->getWorld()->createRenderable("box");
    entity->position = glm::vec3(0, 2.0f, 0);
    entity->color = glm::vec3(0, 0, 1.0f);
    generalShader = new ShaderProgram();
    generalShader->load("./shaders/quad_vertex.glsl", "./shaders/quad_fragment.glsl");
    vbo = VertexBuffer::createQuad();

    WorldLoader loader(game->scene->getWorld());
    loader.load("./worlds/LevelOne-1.0.xml");
}

void SpyE::update(float dt) {
    if (!active)
        return;

    entity->pivot = glm::vec3(0.0f, 0.0f, 0.0f);
    game->scene->camera->position = glm::vec3(entity->getPosition().x, entity->getPosition().y+10.0f, entity->getPosition().z + 20.0f);
    game->scene->camera->lookAt(game->scene->camera->position, entity->getPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
    game->scene->camera->focus = entity->getPosition();

    if (game->input->justPressed("Left Click"))
        printf("clicked\n");

}

