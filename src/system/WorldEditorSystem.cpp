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
#include "sound/SoundManager.h"
#include <graphics/Shader.h>

#include "world/Camera.h"


float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float mouseSpeed = 0.005f;
float speed = 10.0f;

WorldEditorSystem::WorldEditorSystem(Game *game) {
    this->game = game;

    Mesh* mesh = new Mesh();
    ObjLoader* objLoader = new ObjLoader();
    mesh->setVertexBuffer(objLoader->loadOBJ("./assets/entities/box/box.obj"));
    Renderable* entity = game->scene->getWorld()->createRenderable();
    entity->position = glm::vec3(0,0,0);
    entity->mesh = mesh;


    Mesh* floorMesh = new Mesh();
    floorMesh->setVertexBuffer(objLoader->loadOBJ("./assets/entities/floor/floor.obj"));
    Renderable* floorEntity = game->scene->getWorld()->createRenderable();
    floorEntity->position = glm::vec3(0,-1.0f,0);
    floorEntity->mesh = floorMesh;



    game->input->mapButton("W", new KeyboardButtonHandler(SDL_SCANCODE_W, game->input));
    game->input->mapButton("A", new KeyboardButtonHandler(SDL_SCANCODE_A, game->input));
    game->input->mapButton("S", new KeyboardButtonHandler(SDL_SCANCODE_S, game->input));
    game->input->mapButton("D", new KeyboardButtonHandler(SDL_SCANCODE_D, game->input));
    game->input->mapButton("Escape", new KeyboardButtonHandler(SDL_SCANCODE_ESCAPE, game->input));
    game->input->mapButton("Left Click", new MouseButtonHandler(SDL_BUTTON_LEFT, game->input));
    game->input->mapButton("Right Click", new MouseButtonHandler(SDL_BUTTON_RIGHT, game->input));


    generalShader = new ShaderProgram();
    generalShader->load("./shaders/quad_vertex.glsl", "./shaders/quad_fragment.glsl");
    vbo = VertexBuffer::createQuad();

    game->scene->camera->position = glm::vec3(0.0f,0.0f,5.0f);
    game->scene->camera->focus = glm::vec3(0.0f,0.0f,0.0f);

    manager = new SoundManager(1);
	manager->play(manager->load("assets/sounds/0x1b.wav"));
}

void WorldEditorSystem::update(float dt) {

    double mouseX = game->input->getMouse()->mouseX;
    double mouseY = game->input->getMouse()->mouseY;

    horizontalAngle += mouseSpeed * float(game->width/2 - mouseX);
    verticalAngle += mouseSpeed * float(game->height/2 - mouseY);

    SDL_Window* window = game->input->mainWindow;

    game->input->getMouse()->setPosition(game->width/2, game->height/2, window);

    glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle),
                        sin(verticalAngle),
                        cos(verticalAngle) * cos(horizontalAngle));

    glm::vec3 right = glm::vec3(sin(horizontalAngle - 3.14f/2.0f),0,cos(horizontalAngle - 3.14f/2.0f));
    glm::vec3 up = glm::cross( right, direction );
    glm::vec3 target = game->scene->camera->position;
    target += direction;
    game->scene->camera->lookAt(game->scene->camera->position, target, up);

    if (game->input->justPressed("Left Click"))
        printf("left clicked\n");

    if (game->input->justPressed("Right Click"))
        printf("right clicked\n");


    if (game->input->isPressed("W")) {
        game->scene->camera->position += direction * dt * speed;

    }
    if (game->input->isPressed("A")) {
        game->scene->camera->position -= right * dt * speed;


    }
    if (game->input->isPressed("S")) {
        game->scene->camera->position -= direction * dt * speed;


    }
    if (game->input->isPressed("D")) {
        game->scene->camera->position += right * dt * speed;

    }

    if (game->input->wasReleased("Escape")) {
        delete manager;
        game->quit = true;
    }
}

void WorldEditorSystem::draw() {

}

void WorldEditorSystem::draw2D() {

}
