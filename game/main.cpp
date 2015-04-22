
#include "logic/Game.h"
#include "world/Scene.h"
#include "graphics/Mesh.h"
#include "resource/ObjLoader.h"
#include "graphics/Renderable.h"
#include "input/KeyboardButtonHandler.h"
#include "input/MouseButtonHandler.h"
#include "world/Camera.h"
#include "SpyE.h"
#include <world/WorldLoader.h>
#include <graphics/Shader.h>
#include "MainMenu.h"
#include "InputState.h"

Game* game;

int main(int argc, char* argv[])
{
    game = new Game();
    SpyE *spye = new SpyE(game);
    MainMenu *mainmenu = new MainMenu(game);
    InputState* inputState = new InputState(game, spye, mainmenu);

	game->getController()->addState("Mainmenu");
	game->getController()->addState("Default");


	game->getController()->addCoreSystem(inputState);
    game->getController()->addSystem("Mainmenu", mainmenu);
	game->getController()->addSystem("Default", spye);

   
    game->getController()->setState("Mainmenu");
    if (game->init(800, 600, "Spy-E", false)) {
        game->update();
    }

    game->end();
    delete game;
    return 0;
}
