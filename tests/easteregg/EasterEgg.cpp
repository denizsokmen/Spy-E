#include "EasterEgg.h"
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
#include "graphics/ui/TextView.h"
#include "graphics/ui/Primitives.h"
#include "sound/Sounds.h"
#include "world/Light.h"

Game *game;

int main(int argc, char *argv[]) {
    game = new Game();
    if (game->init(640, 480, "Spy-E", false)) {
        EasterEgg *test = new EasterEgg(game);
        game->getController()->addCoreSystem(test);
        game->update();
    }

    game->end();
    delete game;
    return 0;
}

EasterEgg::EasterEgg(Game * game) {
    this->game = game;
    entity = game->scene->getWorld()->createRenderable("box");
    entity->setPosition(glm::vec3(0, 10.0f, 0));
    entity->setColor(glm::vec3(0, 0, 1.0f));
    //glm::mat4 trans = glm::scale(entity->getTransformation(), glm::vec3(2.0f, 2.0f, 2.0f));

    physicsWorld = game->physics->getWorld();
    assignKeyboardInputs(game);
    assignMouseInputs(game);


    generalShader = new ShaderProgram();
    generalShader->load("./shaders/quad_vertex.glsl", "./shaders/quad_fragment.glsl");
    vbo = VertexBuffer::createQuad();


    WorldLoader loader(game->scene->getWorld());
    loader.load("./worlds/level1/");

    for (int i = 1; i < loader.world->getRenderables().size(); i++) {
        Renderable *entityTemp = loader.world->getRenderables()[i];
        physicsWorld->createBody(entityTemp, entityTemp->getVertexBuffer()->vertexList);
    }

    box = physicsWorld->createBody(entity, entity->getVertexBuffer()->vertexList);
    box->setAcceleration(-30.0f, 'y');


    Light *light = new Light();
    light->type = LIGHT_POINT;
    light->setPosition(glm::vec3(0, -1, 1));
    light->intensities = glm::vec3(1.0, 1.0, 1.0);
    light->coneAngle = 359.0f;
    light->coneDirection = glm::vec3(0, -0.5, -1);
    light->ambientCoefficient = 0.01f;
    light->attenuation = 0.01f;
    game->scene->getWorld()->addLight(light);

    Image *image = new Image("./assets/texture/easteregg/menu.png");
    image->setFrame(Rect(0, game->height - 81, 681, 81));
    game->gui->addSubview(image);


    TextView *textView = new TextView();
    textView->setFrame(Rect(game->width / 2, game->height / 2, 200, 400));
    textView->setText(L"YOU ARE IN DOOM NOW YOU ARE IN DOOM NOW YOU ARE IN DOOM NOW YOU ARE IN DOOM NOW");
    game->gui->addSubview(textView);

    game->sounds->open("doom", "assets/sounds/doom.wav");
    game->sounds->play("doom");

}

void EasterEgg::update(float dt) {


    game->scene->camera->position = glm::vec3(entity->getPosition().x, entity->getPosition().y + 10.0f,
                                              entity->getPosition().z + -10.0f);
    game->scene->camera->lookAt(game->scene->camera->position, entity->getPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
    game->scene->camera->focus = entity->getPosition();
   
    if (game->input->isPressed("Left")) {
        entity->setOrientation(glm::rotate(entity->getOrientation(), 90.0f * dt, glm::vec3(0.0f, 1.0f, 0.0f)));
    }

	if (game->input->isPressed("Right")) {
		entity->setOrientation(glm::rotate(entity->getOrientation(), 90.0f * dt, glm::vec3(0.0f, -1.0f, 0.0f)));
    }

    if (game->input->isPressed("Up")) {
        glm::vec3 forward = glm::normalize(entity->getOrientation() * glm::vec3(0.0f, 0.0f, 1.0f));
        box->setAcceleration(forward.x * 10.0f, 'x');
        box->setAcceleration(forward.z * 10.0f, 'z');
    } else if (game->input->isPressed("Down")) {
        glm::vec3 back = glm::normalize(entity->getOrientation() * glm::vec3(0.0f, 0.0f, -1.0f));
        box->setAcceleration(back.x * 10.0f, 'x');
        box->setAcceleration(back.z * 10.0f, 'z');
    } else if (!game->input->isPressed("Down") && !game->input->isPressed("Up")) {
        box->setAcceleration(0, 'x');
        box->setAcceleration(0, 'z');
    }

    if (game->input->isPressed("Space"))
        box->setSpeed(10.0f, 'y');

    if (game->input->justPressed("B"))
        physicsWorld->bounce = !physicsWorld->bounce;


    if (game->input->wasReleased("Escape") || game->input->quit)
        game->quit = true;

    physicsWorld->update(dt);

}

void EasterEgg::assignMouseInputs(Game * game) {/*  Use keycodes given below for mouse input:
    *	SDL_BUTTON_LEFT
    *	SDL_BUTTON_RIGHT
    *	SDL_BUTTON_MIDDLE
    *	SDL_BUTTON_X1
    *	SDL_BUTTON_X2
    */
    game->input->mapButton("Left Click", new MouseButtonHandler(SDL_BUTTON_LEFT, game->input));
}

void EasterEgg::assignKeyboardInputs(Game * game) {/*Use scan codes for mapping keyboard from now on. For full list of scan codes:
	*	check SDL_scancode.h
	*	OR
	*	https://wiki.libsdl.org/SDLScancodeLookup
	*/
    game->input->mapButton("Escape", new KeyboardButtonHandler(SDL_SCANCODE_ESCAPE, game->input));
    game->input->mapButton("Left", new KeyboardButtonHandler(SDL_SCANCODE_LEFT, game->input));
    game->input->mapButton("Right", new KeyboardButtonHandler(SDL_SCANCODE_RIGHT, game->input));
    game->input->mapButton("Down", new KeyboardButtonHandler(SDL_SCANCODE_DOWN, game->input));
    game->input->mapButton("Up", new KeyboardButtonHandler(SDL_SCANCODE_UP, game->input));
    game->input->mapButton("Space", new KeyboardButtonHandler(SDL_SCANCODE_SPACE, game->input));
    game->input->mapButton("B", new KeyboardButtonHandler(SDL_SCANCODE_B, game->input));
}

void EasterEgg::draw() {

}

void EasterEgg::draw2D() {
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