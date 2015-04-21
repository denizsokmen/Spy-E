//
// Created by Taha Doğan Güneş on 18/03/15.
//

#include <logic/Game.h>
#include "TestSound.h"
#include "graphics/Mesh.h"
#include "resource/ObjLoader.h"
#include "graphics/Renderable.h"
#include "world/Scene.h"
#include "input/KeyboardButtonHandler.h"
#include "input/MouseButtonHandler.h"
#include "sound/Sounds.h"
#include "graphics/Shader.h"
#include "world/Camera.h"

float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float mouseSpeed = 0.005f;
float speed = 10.0f;
int sound_1;

Game* game;

int main(int argc, char* argv[])
{
    game = new Game();
    if (game->init(640, 480, "Spy-E", false)){
        SoundSystem *test = new SoundSystem(game);
        game->getController()->addCoreSystem(test);
        game->update();
    }

    game->end();
    delete game;
    return 0;
}

SoundSystem::SoundSystem(Game *game){
    this->game = game;

    Renderable* entity = game->scene->getWorld()->createRenderable("box");
    entity->setPosition(glm::vec3(0,0,0));
    entity->setColor(glm::vec3(1.0,1.0,1.0));

    Renderable* entity2 = game->scene->getWorld()->createRenderable("cube");
	entity2->setPosition(glm::vec3(2.0, 0, 0));
	entity2->setColor(glm::vec3(0.5, 1.0, 1.0));

    Renderable* entity3 = game->scene->getWorld()->createRenderable("cube");
	entity3->setPosition(glm::vec3(-2.0, 0.0, 0));
	entity3->setColor(glm::vec3(0.5, 0.5, 1.0));

    soundcube = game->scene->getWorld()->createRenderable("cube");
	soundcube->setPosition(glm::vec3(0.0, 10.0, 0));
	soundcube->setColor(glm::vec3(0.2, 0.2, 0.2));

    Renderable* floorEntity = game->scene->getWorld()->createRenderable("floor");
	floorEntity->setPosition(glm::vec3(0, -2.0f, 0));
	floorEntity->setColor(glm::vec3(1.0, 1.0, 1.0));

    game->input->mapButton("W", new KeyboardButtonHandler(SDL_SCANCODE_W, game->input));
    game->input->mapButton("A", new KeyboardButtonHandler(SDL_SCANCODE_A, game->input));
    game->input->mapButton("S", new KeyboardButtonHandler(SDL_SCANCODE_S, game->input));
    game->input->mapButton("D", new KeyboardButtonHandler(SDL_SCANCODE_D, game->input));

    game->input->mapButton("Up", new KeyboardButtonHandler(SDL_SCANCODE_UP, game->input));
    game->input->mapButton("Left", new KeyboardButtonHandler(SDL_SCANCODE_LEFT, game->input));
    game->input->mapButton("Right", new KeyboardButtonHandler(SDL_SCANCODE_RIGHT, game->input));
    game->input->mapButton("Down", new KeyboardButtonHandler(SDL_SCANCODE_DOWN, game->input));
    game->input->mapButton("Escape", new KeyboardButtonHandler(SDL_SCANCODE_ESCAPE, game->input));
    game->input->mapButton("Left Click", new MouseButtonHandler(SDL_BUTTON_LEFT, game->input));
    game->input->mapButton("Right Click", new MouseButtonHandler(SDL_BUTTON_RIGHT, game->input));

    generalShader = new ShaderProgram();
    generalShader->load("./shaders/quad_vertex.glsl", "./shaders/quad_fragment.glsl");
    vbo = VertexBuffer::createQuad();

    game->scene->camera->position = glm::vec3(0.0f,0.0f,5.0f);
    game->scene->camera->focus = glm::vec3(0.0f,0.0f,0.0f);

    sound_1 = game->sounds->open("assets/sounds/beep-01a.wav");
    game->sounds->loop(sound_1, true);
    game->sounds->play(sound_1);
        
}

void SoundSystem::update(float dt){
    double mouseX = game->input->getMouse()->mouseX;
    double mouseY = game->input->getMouse()->mouseY;

    horizontalAngle = mouseSpeed * float(game->width/2 - mouseX);
    verticalAngle = mouseSpeed * float(game->height/2 - mouseY);

    SDL_Window* window = game->input->mainWindow;

    if(game->input->focus) //TODO: all game should be inside this loop
        game->input->getMouse()->setPosition(game->width/2, game->height/2, window);

	 game->scene->camera->fpsRotation(horizontalAngle*25.0f, verticalAngle*25.0f);

    if (game->input->justPressed("Left Click")){
        game->sounds->play(sound_1); 
        printf("Left clicked, sound playing...    \n");
    }

    if (game->input->justPressed("Right Click")){
        game->sounds->stop(sound_1);
        printf("Right clicked, sound stopped...   \n");
    }

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

    if (game->input->isPressed("Up")) {
		glm::vec3 pos = soundcube->getPosition();
        pos.y += 5.0f * dt;
		soundcube->setPosition(pos);

    }
    if (game->input->isPressed("Left")) {
		glm::vec3 pos = soundcube->getPosition();
		pos.x -= 5.0f * dt;
		soundcube->setPosition(pos);
    }

    if (game->input->isPressed("Right")) {
		glm::vec3 pos = soundcube->getPosition();
		pos.x += 5.0f * dt;
		soundcube->setPosition(pos);
    }

    if (game->input->isPressed("Down")) {
		glm::vec3 pos = soundcube->getPosition();
		pos.y -= 5.0f * dt;
		soundcube->setPosition(pos);
    }

    if (game->input->wasReleased("Escape") || game->input->quit){
        game->quit = true;
    }

	glm::vec3 pos = soundcube->getPosition();
    game->sounds->set_source_position(sound_1,
                                    pos.x,
                                    pos.y,
                                    pos.z);

    game->sounds->set_listener_position(game->scene->camera->position.x,
                                        game->scene->camera->position.y,
                                        game->scene->camera->position.z);



    Camera* cam = game->scene->camera;
    glm::vec3 dirup = glm::vec3(cam->view[0][1], cam->view[1][1], cam->view[2][1]);
    glm::vec3 dir = -glm::vec3(cam->view[0][2], cam->view[1][2], cam->view[2][2]);
    //glm::vec3 dir = game->scene->camera->orientation * glm::vec3(0.0f, 0.0f, -1.0f);
    //glm::vec3 dirup = game->scene->camera->orientation * glm::vec3(0.0f, 1.0f, 0.0f);
    game->sounds->set_listener_orientation(dir.x, dir.y, dir.z,
                                           dirup.x, dirup.y, dirup.z
                                            );

}

void SoundSystem::draw(){}

void SoundSystem::draw2D(){}
