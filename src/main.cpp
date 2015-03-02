//
//  main.cpp
//  Agile
//
//  Created by Deniz Sokmen on 10/02/15.
//  Copyright (c) 2015 CS476. All rights reserved.
//
#include <stdbool.h>
#include <iostream>
#include "Game.h"
#include "TestGameSystem.h"

Game* game;

int main( void )
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

