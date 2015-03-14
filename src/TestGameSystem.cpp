#include "TestGameSystem.h"
#include "logic/Game.h"
#include "world/Scene.h"
#include "graphics/Mesh.h"
#include "graphics/Objloader.h"
#include "graphics/Renderable.h"
#include "input/KeyboardButtonHandler.h"
#include "input/MouseButtonHandler.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <world/WorldLoader.h>


TestGameSystem::TestGameSystem(Game *game) {
	this->game = game;
    Mesh* mesh = new Mesh();
    ObjLoader* objLoader = new ObjLoader();
    mesh->setVertexBuffer(objLoader->loadOBJ("./assets/entities/camera/camera-bottom.obj"));
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

    //entity->setTransformation(trans);


    //    World *world = new World();
//    Entity *entity = new Entity();
////    entity->name = "Box";
//    world->addEntity(entity);
//
//
//    WorldExporter *exporter = new WorldExporter();
//    exporter->save("HelloWorld","1.0", "./worlds/", world);

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

   // entity->setTransformation(trans);
}

void TestGameSystem::draw() {

}