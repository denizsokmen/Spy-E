#include "TestGUI.h"
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
#include "sound/Sounds.h"
#include "graphics/ui/TextView.h"
#include "graphics/ui/Primitives.h"

Game *game;

int main(int argc, char *argv[]) {
    game = new Game();
    if (game->init(640, 480, "Spy-E - GUI Tests", false)) {
        TestGUI *test = new TestGUI(game);
        game->getController()->addCoreSystem(test);
        game->update();
    }

    game->end();
    delete game;
    return 0;
}

TestGUI::TestGUI(Game *game) {
    this->game = game;
    entity = game->scene->getWorld()->createRenderable("rabbit");
	entity->setPosition(glm::vec3(5.0f, 0.0f, 0));
    entity->setScale(glm::vec3(5.0f, 5.0f, 5.0f));
    entity->setColor(glm::vec3(0, 0, 1.0f));

    //glm::mat4 trans = glm::scale(entity->getTransformation(), glm::vec3(2.0f, 2.0f, 2.0f));

    physics = new Physics();
    assignKeyboardInputs(game);
    assignMouseInputs(game);

    generalShader = new ShaderProgram();
    generalShader->load("./shaders/quad_vertex.glsl", "./shaders/quad_fragment.glsl");
    vbo = VertexBuffer::createQuad();

    WorldLoader loader(game->scene->getWorld());
    loader.load("./worlds/Level2/");

    for (int i = 1; i < loader.world->getRenderables().size(); i++) {
        Renderable *entityTemp = loader.world->getRenderables()[i];
        physics->getWorld()->createBody(entityTemp, entityTemp->getVertexBuffer()->vertexList);
    }

    box = physics->getWorld()->createBody(entity, entity->getVertexBuffer()->vertexList);
    box->setAcceleration(-30.0f, 'y');

    Image *image = new Image("./assets/texture/menu/logo.png");
    image->setTag("image1");
    image->setFrame(Rect(game->width - 140, game->height - 25, 140, 140));
    game->gui->addSubview(image);

    fpsLabel = new Label(L"FPS: 0");
    fpsLabel->setFrame(Rect(0, game->height - 20, 300, 100));
    game->gui->addSubview(fpsLabel);

    TextView *textView = new TextView();
    textView->setFrame(Rect(10, 10, 400, 800));
    textView->setText(L"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur hendrerit, massa et dignissim rutrum, ex nisi egestas est, eu vestibulum quam ante eu purus. Pellentesque tellus lectus, euismod id efficitur non, vehicula eget mi.");
    game->gui->addSubview(textView);

    game->input->showCursor(true);

   // game->sounds->open("asd", "assets/sounds/0x1b.wav");
    //game->sounds->play("asd");


}

void TestGUI::update(float dt) {

    fpsLabel->setText(L"FPS: %f", game->fps);

    game->scene->camera->position = glm::vec3(entity->getPosition().x, entity->getPosition().y + 10.0f,
                                              entity->getPosition().z + -10.0f);
    game->scene->camera->lookAt(game->scene->camera->position, entity->getPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
    game->scene->camera->focus = entity->getPosition();
    //entity->position += glm::vec3(0.000f, 0.00f, -3.0f*dt);

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
    } else if (!game->input->isPressed("Down") && !game->input->isPressed("Up")){
        box->setAcceleration(0, 'x');
        box->setAcceleration(0, 'z');
    }

    if (game->input->isPressed("Space"))
        box->setSpeed(10.0f, 'y');

    if (game->input->justPressed("B"))
        physics->getWorld()->bounce = !physics->getWorld()->bounce;

    if (game->input->wasReleased("Escape") || game->input->quit)
        game->quit = true;
}

void TestGUI::assignMouseInputs(Game *game) {/*  Use keycodes given below for mouse input:
    *	SDL_BUTTON_LEFT
    *	SDL_BUTTON_RIGHT
    *	SDL_BUTTON_MIDDLE
    *	SDL_BUTTON_X1
    *	SDL_BUTTON_X2
    */
    game->input->mapButton("Left Click", new MouseButtonHandler(SDL_BUTTON_LEFT, game->input));
}

void TestGUI::assignKeyboardInputs(Game *game) {/*Use scan codes for mapping keyboard from now on. For full list of scan codes:
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
    game->input->mapButton("W", new KeyboardButtonHandler(SDL_SCANCODE_W, game->input));
    game->input->mapButton("A", new KeyboardButtonHandler(SDL_SCANCODE_A, game->input));
    game->input->mapButton("S", new KeyboardButtonHandler(SDL_SCANCODE_S, game->input));
    game->input->mapButton("D", new KeyboardButtonHandler(SDL_SCANCODE_D, game->input));
    game->input->mapButton("Left Click", new MouseButtonHandler(SDL_BUTTON_LEFT, game->input));
    game->input->mapButton("Right Click", new MouseButtonHandler(SDL_BUTTON_RIGHT, game->input));
}

void TestGUI::draw() {

}

void TestGUI::draw2D() {
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