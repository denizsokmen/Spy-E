//
// Created by Taha Doğan Güneş on 18/03/15.
//

#include <logic/Game.h>
#include "graphics/FontSDL.h"
#include "TestWorldEditor.h"
#include "graphics/Mesh.h"
#include "graphics/ObjLoader.h"
#include "graphics/Renderable.h"
#include "world/Scene.h"
#include "input/KeyboardButtonHandler.h"
#include "input/MouseButtonHandler.h"
#include "sound/SoundManager.h"
#include "graphics/Shader.h"
#include "world/Camera.h"
#include "utils/FPS.h"

float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float mouseSpeed = 0.005f;
float speed = 10.0f;



Game* game;

int main(int argc, char* argv[])
{
    game = new Game();
    if (game->init(640, 480, "Spy-E", false)) {
        //TestGameSystem *test = new TestGameSystem(game);
        WorldEditorSystem *test = new WorldEditorSystem(game);
        // TestPhysics *test = new TestPhysics(game);
        game->getController()->addCoreSystem(test);
        game->update();
    }



    game->end();
    delete game;
    return 0;
}


WorldEditorSystem::WorldEditorSystem(Game *game) {
    this->game = game;


    Renderable* entity = game->scene->getWorld()->createRenderable("box");
    entity->position = glm::vec3(0,0,0);
    entity->color = glm::vec3(1.0,1.0,1.0);



    Renderable* entity2 = game->scene->getWorld()->createRenderable("cube");
    entity2->position = glm::vec3(2.0,0,0);
    entity2->color = glm::vec3(0.5,1.0,1.0);



    Renderable* entity3 = game->scene->getWorld()->createRenderable("cube");
    entity3->position = glm::vec3(-2.0,0.0,0);
    entity3->color = glm::vec3(0.5,0.5,1.0);


    Renderable* floorEntity = game->scene->getWorld()->createRenderable("floor");
    floorEntity->position = glm::vec3(0,-2.0f,0);
    floorEntity->color = glm::vec3(1.0,1.0,1.0);



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

    manager = new SoundManager();
	manager->open("asd","assets/sounds/0x1b.wav");
    manager->play("asd");

    font = new FontSDL(game->drawer);
    font->loadFont("fonts/Abstract.ttf",16);

    fps = new FPS();
}

void WorldEditorSystem::update(float dt) {

    //std::wstring s = std::wstring(L"FPS-") + std::to_wstring(fps->get());
    font->draw(glm::vec3(20, game->height-60, 0.0), L"asdasdasfsd\nf~~ ;_; FPS - %d",fps->get());
    double mouseX = game->input->getMouse()->mouseX;
    double mouseY = game->input->getMouse()->mouseY;

    horizontalAngle = mouseSpeed * float(game->width/2 - mouseX);
    verticalAngle = mouseSpeed * float(game->height/2 - mouseY);

    SDL_Window* window = game->input->mainWindow;

    if(game->input->focus) //TODO: all game should be inside this loop
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

    if (game->input->wasReleased("Escape") || game->input->quit) {
        delete manager;
        game->quit = true;
    }

    fps->update(dt);
}

void WorldEditorSystem::draw() {

}

void WorldEditorSystem::draw2D() {

}
