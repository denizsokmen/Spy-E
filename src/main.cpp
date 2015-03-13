#include <stdbool.h>
#include <iostream>

#include "world/WorldExporter.h"
#include "world/WorldLoader.h"

#include "TestGameSystem.h"

#include "logic/Game.h"
#include "world/World.h"
#include "world/Entity.h"

Game* game;

#if defined _WIN32 || defined __CYGWIN__
#include <windows.h>
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{

    game = new Game();
    if (game->init(640, 480, "Spy-E", false)) {
        TestGameSystem *test = new TestGameSystem(game);
        game->getController()->addCoreSystem(test);
        game->update();
    }



    game->end();
    delete game;
    return 0;

}
#else
int main(int argc, char* argv[])
{
    game = new Game();
    if (game->init(640, 480, "Spy-E", false)) {
        TestGameSystem *test = new TestGameSystem(game);
        game->getController()->addCoreSystem(test);
        game->update();
    }



    game->end();
    delete game;
    return 0;
}
#endif