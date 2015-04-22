#include "TestGameSystem.h"
#include <world/WorldLoader.h>


Game* game;

int main(int argc, char* argv[])
{
    game = new Game();
    if (game->init(800, 600, "Spy-E", false)) {
        TestGameSystem *test = new TestGameSystem(game);
        game->getController()->addCoreSystem(test);
        game->update();
    }

    game->end();
    delete game;
    return 0;
}

TestGameSystem::TestGameSystem(Game *game) {
	this->game = game;
    entity = game->scene->getWorld()->createRenderable("rabbit");
    entity->setPosition(glm::vec3(0, 10.0f, 0));
    entity->setColor(glm::vec3(0, 0, 1.0f));
    entity->setScale(glm::vec3(3.0f, 3.0f, 3.0f));
    //glm::mat4 trans = glm::scale(entity->getTransformation(), glm::vec3(2.0f, 2.0f, 2.0f));

    physics = game->physics;
    assignKeyboardInputs(game);
    assignMouseInputs(game);



    generalShader = new ShaderProgram();
    generalShader->load("./shaders/quad_vertex.glsl", "./shaders/quad_fragment.glsl");
    vbo = VertexBuffer::createQuad();



    WorldLoader loader(game->scene->getWorld());
    loader.load("./worlds/LevelOne-1.0.xml");

    for(int i = 1; i < loader.world->getRenderables().size(); i++) {
        Renderable* entityTemp = loader.world->getRenderables()[i];
        physics->getWorld()->createBody(entityTemp, entityTemp->getVertexBuffer()->vertexList);
    }

    box = physics->getWorld()->createBody(entity, entity->getVertexBuffer()->vertexList);
    box->setAcceleration(-30.0f, 'y');


}

void TestGameSystem::update(float dt) {
    //glm::mat4 trans = glm::translate(entity->getTransformation(), glm::vec3(dt, dt, dt));
    //glm::mat4 trans = glm::rotate(entity->getTransformation(), 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));




    glm::vec3 dir = entity->getOrientation() * glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 dirup = entity->getOrientation() * glm::vec3(0.0f, 1.0f, 0.0f);

    game->scene->camera->position = glm::mix(game->scene->camera->position, entity->getPosition() + ((dirup * 5.0f) + (dir * 10.0f)), 0.01f);
    game->scene->camera->lookAt(game->scene->camera->position, entity->getPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
    game->scene->camera->focus = entity->getPosition();


    if (game->input->isPressed("Left")) {
        entity->setOrientation(glm::rotate(entity->getOrientation(), glm::radians(120.0f * dt), glm::vec3(0.0f, 1.0f, 0.0f)));
    }

	if (game->input->isPressed("Right")) {
		entity->setOrientation(glm::rotate(entity->getOrientation(), glm::radians(120.0f * dt), glm::vec3(0.0f, -1.0f, 0.0f)));
    }
    
    if (game->input->isPressed("Up")) {
        glm::vec3 forward = glm::normalize(entity->getOrientation() * glm::vec3(0.0f, 0.0f, 1.0f));
        box->setAcceleration(forward.x * 10.0f, 'x');
        box->setAcceleration(forward.z * 10.0f, 'z');
    } else if (game->input->isPressed("Down")) {
		glm::vec3 back = glm::normalize(entity->getOrientation() * glm::vec3(0.0f, 0.0f, -1.0f));
        box->setAcceleration(back.x * 10.0f, 'x');
        box->setAcceleration(back.z * 10.0f, 'z');
    } else if (!game->input->isPressed("Down") && !game->input->isPressed("Up")){
        box->setAcceleration(0, 'x');
        box->setAcceleration(0, 'z');
    }

	glm::vec3 adir = entity->getOrientation() * glm::vec3(0.0f, 0.0f, 1.0f);

    if(game->input->justPressed("Enter")) {


        glm::vec3 loc = box->getLocation() + adir;
        Body* body = this->game->physics->getNearestBody(loc, adir);
        printf("camera position: (%f, %f, %f)\n", game->scene->camera->position.x,
               game->scene->camera->position.y, game->scene->camera->position.z);
        printf("camera direction: (%f, %f, %f)\n", game->scene->camera->viewDirection.x,
               game->scene->camera->viewDirection.y, game->scene->camera->viewDirection.z);
        if (body) {
            printf("Change color\n");
			glm::vec3 col = body->getEntity()->getColor();
            body->getEntity()->setColor(glm::vec3(col.x+0.1,
                                                 col.y+0.1,
												 col.z+0.1));
        }

    }

    if(game->input->isPressed("Space"))
        box->setSpeed(10.0f, 'y');
    else if(game->input->isPressed("Shift"))
        box->setSpeed(-10.0f, 'y');

    if(game->input->justPressed("B"))
        physics->getWorld()->bounce = !physics->getWorld()->bounce;

	if (game->input->wasReleased("Escape") || game->input->quit)
		game->quit = true;


}

void TestGameSystem::assignMouseInputs(Game *game) {
    /*  Use keycodes given below for mouse input:
    *	SDL_BUTTON_LEFT
    *	SDL_BUTTON_RIGHT
    *	SDL_BUTTON_MIDDLE
    *	SDL_BUTTON_X1
    *	SDL_BUTTON_X2
    */
    game->input->mapButton("Left Click", new MouseButtonHandler(SDL_BUTTON_LEFT, game->input));
}

void TestGameSystem::assignKeyboardInputs(Game *game) {/*Use scan codes for mapping keyboard from now on. For full list of scan codes:
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
    game->input->mapButton("LControl", new KeyboardButtonHandler(SDL_SCANCODE_LCTRL, game->input));
    game->input->mapButton("Enter", new KeyboardButtonHandler(SDL_SCANCODE_RETURN, game->input));
    game->input->mapButton("Shift", new KeyboardButtonHandler(SDL_SCANCODE_LSHIFT, game->input));
}

void TestGameSystem::draw() {

}

void TestGameSystem::draw2D() {
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