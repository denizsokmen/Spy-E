//
// Created by Taha Doğan Güneş on 18/03/15.
//

#include <logic/Game.h>
#include "system/WorldEditorSystem.h"
#include "graphics/Mesh.h"
#include "graphics/ObjLoader.h"
#include "graphics/Renderable.h"
#include "world/Scene.h"
#include "input/KeyboardButtonHandler.h"
#include "input/MouseButtonHandler.h"
#include "sound/SoundManager.h"
#include "graphics/Shader.h"
#include "graphics/Cube.h"
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
    Cube* entity = game->scene->getWorld()->createCube();
    entity->position = glm::vec3(0,0,0);
    entity->mesh = mesh;
    entity->color = glm::vec3(1.0,1.0,1.0);



    Mesh* mesh2 = new Mesh();
    mesh2->setVertexBuffer(objLoader->loadOBJ("./assets/entities/box/box.obj"));
    Cube* entity2 = game->scene->getWorld()->createCube();
    entity2->position = glm::vec3(2.0,0,0);
    entity2->mesh = mesh2;
    entity2->color = glm::vec3(0.5,1.0,1.0);



    Mesh* mesh3 = new Mesh();
    mesh3->setVertexBuffer(objLoader->loadOBJ("./assets/entities/box/box.obj"));
    Cube* entity3 = game->scene->getWorld()->createCube();
    entity3->position = glm::vec3(-2.0,0.0,0);
    entity3->mesh = mesh3;
    entity3->color = glm::vec3(0.5,0.5,1.0);


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

    horizontalAngle = mouseSpeed * float(game->width/2 - mouseX);
    verticalAngle = mouseSpeed * float(game->height/2 - mouseY);

    SDL_Window* window = game->input->mainWindow;

    game->input->getMouse()->setPosition(game->width/2, game->height/2, window);


	game->scene->camera->fpsRotation(horizontalAngle*25.0f, verticalAngle*25.0f);

    if (game->input->justPressed("Left Click"))
        printf("left clicked\n");

    if (game->input->justPressed("Right Click"))
        printf("right clicked\n");


    if (game->input->isPressed("W")) {
		game->scene->camera->move(0.0f, 0.0f, speed*dt);

    }
    if (game->input->isPressed("A")) {
		game->scene->camera->move(-speed*dt, 0.0f, 0.0f);


    }
	if (game->input->isPressed("S")) {
		game->scene->camera->move(0.0f, 0.0f, -speed*dt);


    }
	if (game->input->isPressed("D")) {
		game->scene->camera->move(speed*dt, 0.0f, 0.0f);

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
