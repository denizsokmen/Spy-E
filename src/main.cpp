//
//  main.cpp
//  Agile
//
//  Created by Deniz Sokmen on 10/02/15.
//  Copyright (c) 2015 CS476. All rights reserved.
//
#include <stdbool.h>
#include <iostream>

#include "world/WorldExporter.h"
#include "TestGameSystem.h"

#include "logic/Game.h"
#include "world/World.h"
#include "world/Entity.h"

Game* game;

int main(int argc, char* argv[])
{

    World *world = new World();
    Entity *entity = new Entity();
//    entity->name = "Box";
    world->addEntity(entity);


    WorldExporter *exporter = new WorldExporter();
    exporter->save("HelloWorld","1.0", "./worlds/", world);

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

