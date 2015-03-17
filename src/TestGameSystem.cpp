#include "TestGameSystem.h"
#include "logic/Game.h"
#include "world/Scene.h"
#include "graphics/Mesh.h"
#include "graphics/ObjLoader.h"
#include "graphics/Renderable.h"
#include "input/KeyboardButtonHandler.h"
#include "input/MouseButtonHandler.h"
#include "world/Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <world/WorldLoader.h>
#include <graphics/Shader.h>


TestGameSystem::TestGameSystem(Game *game) {
	this->game = game;
    Mesh* mesh = new Mesh();
    ObjLoader* objLoader = new ObjLoader();
    mesh->setVertexBuffer(objLoader->loadOBJ("./assets/entities/box/box.obj"));
    entity = game->scene->getWorld()->createRenderable();
    //glm::mat4 trans = glm::scale(entity->getTransformation(), glm::vec3(2.0f, 2.0f, 2.0f));

    entity->orientation = glm::rotate(entity->orientation, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    entity->mesh = mesh;


	/*Use scancodes for mapping keyboard from now on. For full list of scancodes:
	*	check SDL_scancode.h 
	*	OR
	*	https://wiki.libsdl.org/SDLScancodeLookup
	*/
	game->input->mapButton("Escape", new KeyboardButtonHandler(SDL_SCANCODE_ESCAPE, game->input));

	/*  Use keycodes given below for mouse:
	*	SDL_BUTTON_LEFT
	*	SDL_BUTTON_RIGHT
	*	SDL_BUTTON_MIDDLE
	*	SDL_BUTTON_X1
	*	SDL_BUTTON_X2
	*/
	game->input->mapButton("Left Click", new MouseButtonHandler(SDL_BUTTON_LEFT, game->input));


    generalShader = new ShaderProgram();
    generalShader->load("./shaders/quad_vertex.glsl", "./shaders/quad_fragment.glsl");
    vbo = VertexBuffer::createQuad();

    WorldLoader loader(game->scene->getWorld());
    loader.load("./worlds/HelloWorld-1.0.xml");
}

void TestGameSystem::update(float dt) {
    //glm::mat4 trans = glm::translate(entity->getTransformation(), glm::vec3(dt, dt, dt));
    //glm::mat4 trans = glm::rotate(entity->getTransformation(), 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    entity->orientation = glm::rotate(entity->orientation, 90.0f * dt, glm::vec3(0.0f, 0.0f, 1.0f));
    entity->position += glm::vec3(0.000f, 0.00f, 0.00f);

	if (game->input->wasReleased("Escape"))
		game->quit = true;

    if (game->input->justPressed("Left Click"))
        printf("clicked\n");

   // entity->setTransformation(trans);
}

void TestGameSystem::draw() {

}

void TestGameSystem::draw2D() {
    Camera *cam = game->scene->camera;
    cam->ortho(0, 800, 0, 600);
    glUseProgram(generalShader->id);

    glm::mat4 MVP = cam->projection  * glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 0.0f)),glm::vec3(80.0f, 80.0f, 0.0f));

    glDisable(GL_DEPTH_TEST);
    glUniformMatrix4fv(glGetUniformLocation(generalShader->id, "MVP"), 1, GL_FALSE, &MVP[0][0]);

    vbo->bind();
    vbo->draw();
    vbo->unbind();
}