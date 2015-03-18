//
// Created by Taha Doğan Güneş on 18/03/15.
//

#include <logic/Game.h>
#include "system/WorldEditorSystem.h"
#include "graphics/Mesh.h"
#include "graphics/ObjLoader.h"
#include "graphics/Renderable.h"
#include "world/Entity.h"
#include "world/Scene.h"
#include "input/KeyboardButtonHandler.h"
#include "input/MouseButtonHandler.h"
#include <graphics/Shader.h>
#include "world/Camera.h"

WorldEditorSystem::WorldEditorSystem(Game *game) {
    this->game = game;

    Mesh* mesh = new Mesh();
    ObjLoader* objLoader = new ObjLoader();
    mesh->setVertexBuffer(objLoader->loadOBJ("./assets/entities/box/box.obj"));
    Renderable* entity = game->scene->getWorld()->createRenderable();
    entity->position = glm::vec3(0,0,0);
    entity->mesh = mesh;


    game->input->mapButton("W", new KeyboardButtonHandler(SDL_SCANCODE_W, game->input));
    game->input->mapButton("A", new KeyboardButtonHandler(SDL_SCANCODE_A, game->input));
    game->input->mapButton("S", new KeyboardButtonHandler(SDL_SCANCODE_S, game->input));
    game->input->mapButton("D", new KeyboardButtonHandler(SDL_SCANCODE_D, game->input));
    game->input->mapButton("Left Click", new MouseButtonHandler(SDL_BUTTON_LEFT, game->input));
    game->input->mapButton("Right Click", new MouseButtonHandler(SDL_BUTTON_RIGHT, game->input));

    generalShader = new ShaderProgram();
    generalShader->load("./shaders/quad_vertex.glsl", "./shaders/quad_fragment.glsl");
    vbo = VertexBuffer::createQuad();

    game->scene->camera->position = glm::vec3(0.0f,0.0f,20.0f);
    game->scene->camera->viewDirection = glm::vec3(0.0f,0.0f,20.0f);
}

void WorldEditorSystem::update(float dt) {

    if (game->input->justPressed("Left Click"))
        printf("left clicked\n");

    if (game->input->justPressed("Right Click"))
        printf("right clicked\n");


    if (game->input->isPressed("W")) {
        game->scene->camera->position = glm::vec3(game->scene->camera->position.x+1.0f*dt, game->scene->camera->position.y, game->scene->camera->position.z);
    }
    if (game->input->isPressed("A")) {
        game->scene->camera->position = glm::vec3(game->scene->camera->position.x-1.0f*dt, game->scene->camera->position.y, game->scene->camera->position.z);
    }
    if (game->input->isPressed("S")) {

    }
    if (game->input->isPressed("D")) {

    }

}

void WorldEditorSystem::draw() {

}

void WorldEditorSystem::draw2D() {

}
