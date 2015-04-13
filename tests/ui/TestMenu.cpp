//
// Created by Taha Doğan Güneş on 05/04/15.
//

#include "TestMenu.h"
#include "logic/Game.h"
#include "world/Scene.h"
#include "graphics/Mesh.h"
#include "resource/ObjLoader.h"
#include "graphics/Renderable.h"
#include "graphics/ui/Image.h"

#include "input/KeyboardButtonHandler.h"
#include "input/MouseButtonHandler.h"
#include "world/Camera.h"
#include <world/WorldLoader.h>
#include <graphics/Shader.h>

#include <graphics/ui/GUI.h>
#include <graphics/ui/Label.h>
#include <graphics/ui/Button.h>
#include "sound/Sounds.h"
#include "graphics/ui/TextView.h"
#include "graphics/ui/Primitives.h"
#include "graphics/ui/Menu.h"
#include "graphics/ui/Button.h"
#include "physics/Physics.h"
#include  <functional>

Game *game;

int main(int argc, char *argv[]) {
    game = new Game();
    if (game->init(640, 480, "Spy-E - Test Menu", false)) {
        TestMenu *test = new TestMenu(game);
        game->getController()->addCoreSystem(test);
        game->update();
    }

    game->end();
    delete game;
    return 0;
}

TestMenu::TestMenu(Game *game) {
    this->game = game;
    entity = game->scene->getWorld()->createRenderable("box");
    entity->position = glm::vec3(0, 10.0f, 0);
    entity->color = glm::vec3(0, 0, 1.0f);
    //glm::mat4 trans = glm::scale(entity->getTransformation(), glm::vec3(2.0f, 2.0f, 2.0f));


    assignKeyboardInputs(game);
    assignMouseInputs(game);


    generalShader = new ShaderProgram();
    generalShader->load("./shaders/quad_vertex.glsl", "./shaders/quad_fragment.glsl");
    vbo = VertexBuffer::createQuad();


    WorldLoader loader(game->scene->getWorld());
    loader.load("./worlds/LevelOne-1.0.xml");

    for (int i = 1; i < loader.world->getRenderables().size(); i++) {
        Renderable *entityTemp = loader.world->getRenderables()[i];
        game->physics->getWorld()->createBody(entityTemp, entityTemp->getVertexBuffer()->vertexList);
    }

    box = game->physics->getWorld()->createBody(entity, entity->getVertexBuffer()->vertexList);
    box->setAcceleration(-30.0f, 'y');


    Image *image = new Image("./assets/texture/menu/logo.png");
    image->setFrame(Rect(game->width/2-105, 37.5, 210, 37.5));
    game->gui->addSubview(image);

    fpsLabel = new Label(L"FPS: 0");
    fpsLabel->setFrame(Rect(0, game->height - 20, 300, 100));
    game->gui->addSubview(fpsLabel);



    menu = new Menu();
    menu->setFrame(Rect(40,game->height/2, 300, 300));

    Button* startButton = new Button();
    startButton->setText(L"Start", Normal);
    startButton->setText(L"_Start_", Selected);
    startButton->setTarget(
            [](){
                printf ("Start Button!.\n");
            }
    );
    Button* optionsButton = new Button();
    optionsButton->setText(L"Options", Normal);
    optionsButton->setText(L"_Options_", Selected);
    Button* extraButton = new Button();
    extraButton->setText(L"Extras", Normal);
    extraButton->setText(L"_Extras_", Selected);

    Button* exitButton= new Button();
    exitButton->setText(L"Exit", Normal);
    exitButton->setText(L"Are you done ?", Selected);

    menu->addItem(startButton);
    menu->addItem(optionsButton);
    menu->addItem(extraButton);
    menu->addItem(exitButton);
    menu->setVerticalSpace(16);
    game->gui->addSubview(menu);


    game->sounds->open("select", "assets/sounds/select.wav");
    game->sounds->open("start", "assets/sounds/start.wav");



}

void TestMenu::update(float dt) {

    fpsLabel->setText(L"FPS: %f", game->fps);


    entity->pivot = glm::vec3(0.0f, 0.0f, 0.0f);
    game->scene->camera->position = glm::vec3(entity->getPosition().x, entity->getPosition().y + 10.0f,
                                              entity->getPosition().z + -10.0f);
    game->scene->camera->lookAt(game->scene->camera->position, entity->getPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
    game->scene->camera->focus = entity->getPosition();
    //entity->position += glm::vec3(0.000f, 0.00f, -3.0f*dt);

    entity->orientation = glm::rotate(entity->orientation, 90.0f * dt, glm::vec3(0.0f, 1.0f, 0.0f));



    if (game->input->wasReleased("Up")) {
        menu->moveCursorUp();
        game->sounds->play("select");
    }

    if (game->input->wasReleased("Down")) {
        menu->moveCursorDown();
        game->sounds->play("select");
    }

    if (game->input->wasReleased("Enter")) {
        menu->runSelected();
    }

    if (game->input->wasReleased("Escape") || game->input->quit)
        game->quit = true;

}

void TestMenu::assignMouseInputs(Game *game) {/*  Use keycodes given below for mouse input:
    *	SDL_BUTTON_LEFT
    *	SDL_BUTTON_RIGHT
    *	SDL_BUTTON_MIDDLE
    *	SDL_BUTTON_X1
    *	SDL_BUTTON_X2
    */
    game->input->mapButton("Left Click", new MouseButtonHandler(SDL_BUTTON_LEFT, game->input));
}

void TestMenu::assignKeyboardInputs(Game *game) {/*Use scan codes for mapping keyboard from now on. For full list of scan codes:
	*	check SDL_scancode.h
	*	OR
	*	https://wiki.libsdl.org/SDLScancodeLookup
	*/
    game->input->mapButton("Escape", new KeyboardButtonHandler(SDL_SCANCODE_ESCAPE, game->input));
    game->input->mapButton("Left", new KeyboardButtonHandler(SDL_SCANCODE_LEFT, game->input));
    game->input->mapButton("Right", new KeyboardButtonHandler(SDL_SCANCODE_RIGHT, game->input));
    game->input->mapButton("Down", new KeyboardButtonHandler(SDL_SCANCODE_DOWN, game->input));
    game->input->mapButton("Up", new KeyboardButtonHandler(SDL_SCANCODE_UP, game->input));
    game->input->mapButton("Enter", new KeyboardButtonHandler(SDL_SCANCODE_RETURN, game->input));
    game->input->mapButton("Space", new KeyboardButtonHandler(SDL_SCANCODE_SPACE, game->input));
    game->input->mapButton("B", new KeyboardButtonHandler(SDL_SCANCODE_B, game->input));
}

void TestMenu::draw() {

}

void TestMenu::draw2D() {
//    Camera *cam = game->scene->camera;
//    cam->ortho(0, game->width, 0, game->height);
//    glUseProgram(generalShader->id);
//
//    glm::mat4 MVP = cam->projection  * glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 0.0f)),glm::vec3(80.0f, 80.0f, 0.0f));
//
//    glDisable(GL_DEPTH_TEST);
//    glUniformMatrix4fv(glGetUniformLocation(generalShader->id, "MVP"), 1, GL_FALSE, &MVP[0][0]);
//
//    vbo->bind();
//    vbo->draw();
//    vbo->unbind();
}