//
// Created by Taha Doğan Güneş on 18/03/15.
//

#include <logic/Game.h>
#include <graphics/ui/Label.h>
#include <utils/FileOperations.h>
#include <graphics/ui/Menu.h>
#include <graphics/ui/Button.h>
#include <physics/Body.h>
#include <world/WorldLoader.h>
#include <world/Light.h>
#include <graphics/Billboard.h>
#include "TestWorldEditor.h"
#include "graphics/Mesh.h"
#include "graphics/Renderable.h"
#include "world/Scene.h"
#include "input/KeyboardButtonHandler.h"
#include "input/MouseButtonHandler.h"
#include "graphics/Shader.h"
#include "world/Camera.h"
#include "graphics/ui/GUI.h"

float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float mouseSpeed = 0.005f;
float speed = 10.0f;


Game* game;
int a;
int main(int argc, char* argv[])
{
    game = new Game();
    if (game->init(640, 480, "Spy-E", false)) {

        WorldEditorSystem *worldEditorSystem = new WorldEditorSystem(game);

        game->getController()->addCoreSystem(worldEditorSystem);
        game->update();
    }



    game->end();
    delete game;
    return 0;
}





WorldEditorSystem::WorldEditorSystem(Game *game) {
    this->game = game;





    game->input->mapButton("W", new KeyboardButtonHandler(SDL_SCANCODE_W, game->input));
    game->input->mapButton("A", new KeyboardButtonHandler(SDL_SCANCODE_A, game->input));
    game->input->mapButton("S", new KeyboardButtonHandler(SDL_SCANCODE_S, game->input));
    game->input->mapButton("D", new KeyboardButtonHandler(SDL_SCANCODE_D, game->input));
    game->input->mapButton("Space", new KeyboardButtonHandler(SDL_SCANCODE_SPACE, game->input));
    game->input->mapButton("Escape", new KeyboardButtonHandler(SDL_SCANCODE_ESCAPE, game->input));
    game->input->mapButton("Left Click", new MouseButtonHandler(SDL_BUTTON_LEFT, game->input));
    game->input->mapButton("Right Click", new MouseButtonHandler(SDL_BUTTON_RIGHT, game->input));


    generalShader = new ShaderProgram();
    generalShader->load("./shaders/quad_vertex.glsl", "./shaders/quad_fragment.glsl");
    vbo = VertexBuffer::createQuad();

    game->scene->camera->position = glm::vec3(0.0f,0.0f,5.0f);
    game->scene->camera->focus = glm::vec3(0.0f,0.0f,0.0f);


    Label* entitiesLabel = new Label(L"Entities:");


    Menu* menu = new Menu();


    entitiesLabel->setFrame(((5.0*game->width)/6.0)-20, 10, 100, 100);
    std::vector<std::string> directories = FileOperations::getAllDirectories("./assets/entities/");

    for (auto d : directories) {
        Button* button = new Button();
        button->setText(d);
        button->setTag(d);
        printf("[Entities] %s \n", d.c_str());
        menu->addItem(button);
    }

    Rect menuFrame = Rect((5.0*game->width)/6.0, 30, game->width/8.0, 20*directories.size());
    menu->setFrame(menuFrame);

    game->gui->addSubview(menu);
    game->gui->addSubview(entitiesLabel);
    game->input->showCursor(true);
//
    WorldLoader loader(game->scene->getWorld());
    loader.load("./worlds/level2/");

    billboard = new Billboard("./assets/texture/neon.png");

    Light *light = new Light();
    light->type = LIGHT_SPOT;
    light->setPosition(glm::vec3(0, 15, 20));
    light->intensities = glm::vec3(0.7, 0.6, 0.4);
    light->coneAngle = 359.0f;
    light->coneDirection = glm::vec3(0, -0.5, -1);
    light->ambientCoefficient = 0.01f;
    light->attenuation = 0.01f;

    Light *light2 = new Light();
    light2->type = LIGHT_SPOT;
    light2->setPosition(glm::vec3(0, 15, -5));
    light2->intensities = glm::vec3(0.8, 0.8, 0.8);
    light2->coneAngle = 359.0f;
    light2->coneDirection = glm::vec3(0, -0.5, -1);
    light2->ambientCoefficient = 0.01f;
    light2->attenuation = 0.01f;

    game->scene->getWorld()->addLight(light);
    game->scene->getWorld()->addLight(light2);


}

void WorldEditorSystem::update(float dt) {


    float mouseX = game->input->getMouse()->mouseX;
    float mouseY = game->input->getMouse()->mouseY;


    if (game->input->isPressed("Space")){


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
        if (game->input->isPressed("W"))
            game->scene->camera->move(0.0f, 0.0f, speed*dt);
        if (game->input->isPressed("A"))
            game->scene->camera->move(-speed*dt, 0.0f, 0.0f);
        if (game->input->isPressed("S"))
            game->scene->camera->move(0.0f, 0.0f, -speed*dt);
        if (game->input->isPressed("D"))
            game->scene->camera->move(speed*dt, 0.0f, 0.0f);
    }

    if (game->input->wasReleased("Escape") || game->input->quit) {
        game->quit = true;
    }

    if(game->input->justPressed("Left Click")){
        game->gui->mainView->handleEvents();


        // FIXME: dsokmen, (sadpanda)
        // Partialy based on:
        // - https://github.com/Shervanator/Engine/blob/f442dae0a23ef802ac6ac164b288c4471e30ccf8/src/Ray.cpp#L19

        printf("Mouse: x:%f y:%f \n", mouseX, mouseY);

        glm::vec2 windowSize = glm::vec2(game->width,game->height);

        glm::vec3 rayStart = game->scene->camera->unProject(glm::vec3(game->width / 2,
                                                                      abs(game->height / 2),
                                                                      0.0f),
                                                            windowSize);

        glm::vec3 rayEnd =  game->scene->camera->unProject(glm::vec3(mouseX,
                                                                     float(game->height)-mouseY,
                                                                     1.0f),
                                                           windowSize);

        printf("ray start: (%f, %f, %f) ray end: (%f, %f, %f)\n",rayStart.x, rayStart.y, rayStart.z, rayEnd.x, rayEnd.y, rayEnd.z);
        glm::vec3 rayDirection = glm::normalize(rayEnd-rayStart);

        Body* body = this->game->physics->getNearestBody(game->scene->camera->position, rayDirection);
        printf("camera position: (%f, %f, %f)\n", game->scene->camera->position.x,
               game->scene->camera->position.y, game->scene->camera->position.z);
        printf("camera direction: (%f, %f, %f)\n", game->scene->camera->viewDirection.x,
               game->scene->camera->viewDirection.y, game->scene->camera->viewDirection.z);
        if (body) {
            printf("Change color\n");
			glm::vec3 col = body->getEntity()->getColor();
            body->getEntity()->setColor(glm::vec3(col.x+0.1,
				col.y + 0.1,
				col.z + 0.1));
        }
    }



}

void WorldEditorSystem::draw() {
    billboard->draw(game->scene->camera);
}

void WorldEditorSystem::draw2D() {

}
