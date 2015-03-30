//
// Created by Enes Şenel on 13/03/15.
//

#include "TestPhysics.h"

Game* game;

int main(int argc, char* argv[])
{
    game = new Game();
    if (game->init(640, 480, "Spy-E", false)) {
        //TestGameSystem *test = new TestGameSystem(game);
        TestPhysics *test = new TestPhysics(game);
        // TestPhysics *test = new TestPhysics(game);
        game->getController()->addCoreSystem(test);
        game->update();
    }



    game->end();
    delete game;
    return 0;
}

TestPhysics::TestPhysics(Game *game){

    this->game = game;

    //pink
    entity = game->scene->getWorld()->createRenderable("box");
    entity->position = glm::vec3(0,0,0);
    entity->color = glm::vec3(1.0,1.0,1.0);

    //white
    entity2 = game->scene->getWorld()->createRenderable("box");
    entity2->position = glm::vec3(10, 0, 0);
    entity2->color = glm::vec3(0.5,1.0,1.0);

    //blue
    entity3 = game->scene->getWorld()->createRenderable("box");
    entity3->position = glm::vec3(-5, 0, 0);
    entity3->color = glm::vec3(1.0,1.0,0.5);

    //yellow
    entity4 = game->scene->getWorld()->createRenderable("box");
    entity4->position = glm::vec3(5, 1, 0);
    entity4->color = glm::vec3(1.0,0.5,1.0);

    floor = game->scene->getWorld()->createRenderable("floor");
    floor->position = glm::vec3(0,-5,0);
    floor->color = glm::vec3(1.0, 1.0, 1.0);

    game->input->mapButton("W", new KeyboardButtonHandler(SDL_SCANCODE_W, game->input));
    game->input->mapButton("A", new KeyboardButtonHandler(SDL_SCANCODE_A, game->input));
    game->input->mapButton("S", new KeyboardButtonHandler(SDL_SCANCODE_S, game->input));
    game->input->mapButton("D", new KeyboardButtonHandler(SDL_SCANCODE_D, game->input));
    game->input->mapButton("Escape", new KeyboardButtonHandler(SDL_SCANCODE_ESCAPE, game->input));
    game->input->mapButton("Left Click", new MouseButtonHandler(SDL_BUTTON_LEFT, game->input));
    game->input->mapButton("Right Click", new MouseButtonHandler(SDL_BUTTON_RIGHT, game->input));
    game->input->mapButton("Left", new KeyboardButtonHandler(SDL_SCANCODE_LEFT, game->input));
    game->input->mapButton("Right", new KeyboardButtonHandler(SDL_SCANCODE_RIGHT, game->input));
    game->input->mapButton("Down", new KeyboardButtonHandler(SDL_SCANCODE_DOWN, game->input));
    game->input->mapButton("Up", new KeyboardButtonHandler(SDL_SCANCODE_UP, game->input));
    game->input->mapButton("Shift", new KeyboardButtonHandler(SDL_SCANCODE_LSHIFT, game->input));
    game->input->mapButton("Space", new KeyboardButtonHandler(SDL_SCANCODE_SPACE, game->input));

    generalShader = new ShaderProgram();
    generalShader->load("./shaders/quad_vertex.glsl", "./shaders/quad_fragment.glsl");
    vbo = VertexBuffer::createQuad();

    game->scene->camera->position = glm::vec3(0.0f,0.0f,5.0f);
    game->scene->camera->focus = glm::vec3(0.0f,0.0f,0.0f);

    printf("PHYSICS TEST INITIALIZED! \n");
    printf("------------------------- \n");

    physicsWorld = new PhysicsWorld();
    b1 = physicsWorld->createBody(&entity->position, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), entity->getVertexBuffer()->vertexList);
    b2 = physicsWorld->createBody(&entity2->position, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), entity2->getVertexBuffer()->vertexList);
    b3 = physicsWorld->createBody(&entity3->position, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), entity3->getVertexBuffer()->vertexList);
    b4 = physicsWorld->createBody(&entity4->position, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), entity4->getVertexBuffer()->vertexList);
    floorBody = physicsWorld->createBody(&floor->position, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), floor->getVertexBuffer()->vertexList);

    //Floor Y coordinate
    physicsWorld->floorY = -3.0f;

    //GRAVITIES
    b1->setAcceleration(-30.0f, 'y');
    //b2->setAcceleration(-9.8f, 'y');
    //b3->setAcceleration(-9.8f, 'y');
    //b4->setAcceleration(-9.8f, 'y');


    printf("------------------------- \n");

    font = new FontSDL(game->drawer);
    font->loadFont("fonts/Arial.ttf", 16);

    fps = new FPS();

}

TestPhysics::~TestPhysics(){

}

void TestPhysics::update(float dt) {

    font->draw(glm::vec3(20, game->height-60, 0.0), L"FPS - %d",fps->get());

    double mouseX = game->input->getMouse()->mouseX;
    double mouseY = game->input->getMouse()->mouseY;

    horizontalAngle = mouseSpeed * float(game->width / 2 - mouseX);
    verticalAngle = mouseSpeed * float(game->height / 2 - mouseY);

    SDL_Window *window = game->input->mainWindow;

    if (game->input->focus)
        game->input->getMouse()->setPosition(game->width / 2, game->height / 2, window);

    game->scene->camera->fpsRotation(horizontalAngle * 25.0f, verticalAngle * 25.0f);

    if (game->input->isPressed("W"))
        b1->setSpeed(10.0f, 'z');
    else if (game->input->isPressed("S"))
        b1->setSpeed(-10.0f, 'z');
    else
        b1->setSpeed(0, 'z');

    if (game->input->isPressed("A"))
        b1->setSpeed(-10.0f, 'x');
    else if (game->input->isPressed("D"))
        b1->setSpeed(10.0f, 'x');
    else
        b1->setSpeed(0, 'x');


    if (game->input->isPressed("Space") && b1->getLocation().y <= physicsWorld->floorY+0.1f)
        b1->setSpeed(10.0f, 'y');



    if (game->input->wasReleased("Escape")) game->quit = true;

    if (game->input->isPressed("Up"))   game->scene->camera->move(0.0f, 0.0f, speed*dt);

    if (game->input->isPressed("Down")) game->scene->camera->move(0.0f, 0.0f, -speed*dt);

    if (game->input->isPressed("Left")) game->scene->camera->move(-speed*dt, 0.0f, 0.0f);

    if (game->input->isPressed("Right"))  game->scene->camera->move(speed*dt, 0.0f, 0.0f);

    physicsWorld->update(dt);
    fps->update(dt);

}

void TestPhysics::draw() {

}

void TestPhysics::draw2D() {

}
