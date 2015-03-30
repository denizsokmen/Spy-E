
#include "logic/Game.h"
#include "world/Scene.h"
#include "graphics/Mesh.h"
#include "graphics/ObjLoader.h"
#include "graphics/Renderable.h"
#include "input/KeyboardButtonHandler.h"
#include "input/MouseButtonHandler.h"
#include "world/Camera.h"
#include "SpyE.h"
#include <world/WorldLoader.h>
#include <graphics/Shader.h>
#include "MainMenu.h"

Game* game;

int main(int argc, char* argv[])
{
    game = new Game();
    SpyE *spye = new SpyE(game);
	game->getController()->addState("Mainmenu");
	game->getController()->addSystem("Mainmenu", new MainMenu(game, game->drawer));
    game->getController()->addCoreSystem(spye);
	game->getController()->setState("Mainmenu");
    if (game->init(640, 480, "Spy-E", false)) {


        game->update();
    }

    game->end();
    delete game;
    return 0;
}
