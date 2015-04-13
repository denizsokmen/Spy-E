//
// Created by Enes Şenel on 13/03/15.
//

#include <graphics/Skybox.h>
#include "TestPhysics.h"
#include "graphics/ui/Label.h"
#include "graphics/ui/Primitives.h"
#include "graphics/ui/GUI.h"

Game* game;

int main(int argc, char* argv[])
{
    game = new Game();
    if (game->init(640, 480, "Spy-E", false)) {
        TestPhysics *test = new TestPhysics(game);
        game->getController()->addCoreSystem(test);
        game->update();
    }

    game->end();
    delete game;
    return 0;
}

TestPhysics::TestPhysics(Game *game){

    this->game = game;

    initializeEntities(game);
    initializeShader();
    initializeCamera(game);

    assignInputs(game);
    createBodies();
    applyGravity();

    skybox = new Skybox("./assets/texture/skybox/desert_right.jpg", "./assets/texture/skybox/desert_left.jpg",
                        "./assets/texture/skybox/desert_top.jpg", "./assets/texture/skybox/desert_top.jpg",
                        "./assets/texture/skybox/desert_front.jpg","./assets/texture/skybox/desert_back.jpg");

    fpsLabel = new Label(L"FPS: 0");
    fpsLabel->setFrame(Rect(0, game->height - 20, 300, 100));
    game->gui->addSubview(fpsLabel);

}

void TestPhysics::update(float dt) {

    SDL_Window *window = game->input->mainWindow;


    fpsLabel->setText(L"FPS: %f", game->fps);

    float dist;
    handleMouseInputs(window);
    handleKeyboardInputs(dt);
    setCameraProperties();



    //casting a ray from 0 0 0 in the direction of -1 0 0 to a box in position -5 0 0 with a correct bounding box with no success
    printf("Bool: %d \n", (physics->castRay(glm::vec3(0,0,0), glm::vec3(-1.0f, 0.0f, 0.0f), b3, dist)));
    //distance isn't showing the right value too
    printf("Dist: %f \n", dist);
}

void TestPhysics::setCameraProperties() {
    game->scene->camera->fpsRotation(horizontalAngle * 25.0f, verticalAngle * 25.0f);
}

void TestPhysics::handleKeyboardInputs(float dt) {
    if (game->input->isPressed("W")){
        b1->setAcceleration(10.0, 'z');
    }
    else if (game->input->isPressed("S"))
        b1->setAcceleration(-10.0, 'z');
    else
        b1->setAcceleration(0.0, 'z');

    if (game->input->isPressed("A"))
        b1->setAcceleration(-10.0, 'x');
    else if (game->input->isPressed("D"))
        b1->setAcceleration(10.0, 'x');
    else
        b1->setAcceleration(0.0, 'x');

    if (game->input->isPressed("Space"))
        b1->setAcceleration(10.0, 'y');

    if (game->input->wasReleased("Escape")) game->quit = true;
    if (game->input->isPressed("Up"))   game->scene->camera->move(0.0f, 0.0f, speed *dt);
    if (game->input->isPressed("Down")) game->scene->camera->move(0.0f, 0.0f, -speed *dt);
    if (game->input->isPressed("Left")) game->scene->camera->move(-speed *dt, 0.0f, 0.0f);
    if (game->input->isPressed("Right"))  game->scene->camera->move(speed *dt, 0.0f, 0.0f);
}


void TestPhysics::handleMouseInputs(SDL_Window *window) {
    double mouseX = game->input->getMouse()->mouseX;
    double mouseY = game->input->getMouse()->mouseY;

    horizontalAngle = mouseSpeed * float(game->width / 2 - mouseX);
    verticalAngle = mouseSpeed * float(game->height / 2 - mouseY);

    if (game->input->focus)
        game->input->getMouse()->setPosition(game->width / 2, game->height / 2, window);
}

void TestPhysics::applyGravity() {
    //b1->setAcceleration(gravity, 'y');
}


void TestPhysics::createBodies() {
    this->physics = game->physics;

    b1 = physics->getWorld()->createBody(entity, entity->getVertexBuffer()->vertexList);
    b2 = physics->getWorld()->createBody(entity2, entity2->getVertexBuffer()->vertexList);
    b3 = physics->getWorld()->createBody(entity3, entity3->getVertexBuffer()->vertexList);
    floorBody = physics->getWorld()->createBody(floor, floor->getVertexBuffer()->vertexList);
}

void TestPhysics::initializeCamera(Game *game) {
    game->scene->camera->position = glm::vec3(0.0f,0.0f,5.0f);
    game->scene->camera->focus = glm::vec3(0.0f,0.0f,0.0f);
}

void TestPhysics::initializeShader() {
    generalShader = new ShaderProgram();
    generalShader->load("./shaders/quad_vertex.glsl", "./shaders/quad_fragment.glsl");
    vbo = VertexBuffer::createQuad();
}

void TestPhysics::initializeEntities(Game *game) {
    //pink
    entity = game->scene->getWorld()->createRenderable("box");
    entity->position = glm::vec3(10,0,10);
    entity->color = glm::vec3(1.0,1.0,1.0);

    //white
    entity2 = game->scene->getWorld()->createRenderable("box");
    entity2->position = glm::vec3(10, 0, 0);
    entity2->color = glm::vec3(0.5,1.0,1.0);

    //blue
    entity3 = game->scene->getWorld()->createRenderable("box");
    entity3->position = glm::vec3(-5.0f, 0, 0);
    entity3->color = glm::vec3(1.0,1.0,0.5);

    floor = game->scene->getWorld()->createRenderable("floor");
    floor->position = glm::vec3(0,-5,0);
    floor->color = glm::vec3(1.0, 1.0, 1.0);
}

void TestPhysics::assignInputs(Game *game) {
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
}

TestPhysics::~TestPhysics(){

}

void TestPhysics::draw() {
    skybox->draw(game->scene->camera);
}

void TestPhysics::draw2D() {

}
