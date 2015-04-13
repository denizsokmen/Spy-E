//
// Created by deniz on 27/03/15.
//

#ifndef SPYE_INPUTSTATE_H
#define SPYE_INPUTSTATE_H


#include <logic/System.h>
#include "SpyE.h"

enum GameState {
    STATE_MAINMENU = 0,
    STATE_GAME
};

class GUI;
class Game;
class SpyE;
class MainMenu;

class InputState : public System {


public:
    GameState currentState;

    InputState(Game *game, SpyE *spye, MainMenu* mainmenu);

    ~InputState();
    void init();
    void update(float dt);
    void draw();
    void draw2D();

    Game *game;
    SpyE *spye;
    MainMenu *mainmenu;
};


#endif //SPYE_INPUTSTATE_H
