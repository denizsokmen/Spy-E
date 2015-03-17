#include <stdbool.h>
#include <iostream>

#include "world/WorldExporter.h"
#include "world/WorldLoader.h"

#include "TestGameSystem.h"

#include "logic/Game.h"
#include "world/World.h"
#include "world/Entity.h"

Game* game;


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
