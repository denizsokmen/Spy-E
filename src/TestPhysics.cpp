//
// Created by Enes Şenel on 13/03/15.
//

#include "TestPhysics.h"

TestPhysics::TestPhysics(Game *game){

    this->game = game;

    //yellow
    Mesh* mesh = new Mesh();
    ObjLoader* objLoader = new ObjLoader();
    mesh->setVertexBuffer(objLoader->loadOBJ("./assets/entities/box/box.obj"));
    Cube* entity = game->scene->getWorld()->createCube();
    entity->position = glm::vec3(0,0,0);
    entity->mesh = mesh;
    entity->color = glm::vec3(1.0,1.0,1.0);

    //white
    Mesh* mesh2 = new Mesh();

    mesh2->setVertexBuffer(objLoader->loadOBJ("./assets/entities/box/box.obj"));
    Cube* entity2 = game->scene->getWorld()->createCube();
    entity2->position = glm::vec3(10, 0, 0);
    entity2->mesh = mesh2;
    entity2->color = glm::vec3(0.5,1.0,1.0);

    //blue
    Mesh* mesh3 = new Mesh();
    mesh3->setVertexBuffer(objLoader->loadOBJ("./assets/entities/box/box.obj"));
    Cube* entity3 = game->scene->getWorld()->createCube();
    entity3->position = glm::vec3(1, 0, 0);
    entity3->mesh = mesh3;
    entity3->color = glm::vec3(1.0,1.0,0.5);

    //pink
    Mesh* mesh4 = new Mesh();
    mesh4->setVertexBuffer(objLoader->loadOBJ("./assets/entities/box/box.obj"));
    Cube* entity4 = game->scene->getWorld()->createCube();
    entity4->position = glm::vec3(0, 1, 0);
    entity4->mesh = mesh4;
    entity4->color = glm::vec3(1.0,0.5,1.0);


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

    printf("PHYSICS TEST INITIALIZED! \n");
    printf("------------------------- \n");

    PhysicsWorld *physicsWorld = new PhysicsWorld();
    Body *b1 = physicsWorld->createBody(entity->position, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), entity->getVertexBuffer()->vertexList);
    Body *b2 = physicsWorld->createBody(entity2->position, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), entity2->getVertexBuffer()->vertexList);
    Body *b3 = physicsWorld->createBody(entity3->position, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), entity3->getVertexBuffer()->vertexList);
    Body *b4 = physicsWorld->createBody(entity4->position, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), entity4->getVertexBuffer()->vertexList);


    //b1-b2-b3-b4 -> yellow-white-blue-pink
    if(physicsWorld->isCollided(b1, b2)) printf("yellow Box and white Box Collided \n");
    if(physicsWorld->isCollided(b1, b3)) printf("yellow Box and blue Box Collided \n" );
    if(physicsWorld->isCollided(b1, b4)) printf("yellow Box and pink Box Collided \n" );
    if(physicsWorld->isCollided(b2, b3)) printf("white Box and blue Box Collided \n" );
    if(physicsWorld->isCollided(b2, b4)) printf("white Box and pink Box Collided \n" );
    if(physicsWorld->isCollided(b3, b4)) printf("blue Box and pink Box Collided \n" );

    printf("------------------------- \n");

}

TestPhysics::~TestPhysics(){

}

void TestPhysics::update(float dt) {

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
        game->quit = true;
    }
}

void TestPhysics::draw() {

}

void TestPhysics::draw2D() {

}
