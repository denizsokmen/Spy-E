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

//    World *world = new World();
//    Entity *entity = new Entity();
////    entity->name = "Box";
//    world->addEntity(entity);
//
//
//    WorldExporter *exporter = new WorldExporter();
//    exporter->save("HelloWorld","1.0", "./worlds/", world);

    WorldLoader *loader = new WorldLoader();
    World *worldSecond = loader->load("./worlds/HelloWorld-1.0.xml");


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

