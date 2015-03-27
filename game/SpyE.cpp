//
// Created by deniz on 27/03/15.
//
#ifndef SPYE_H_INC
#define SPYE_H_INC

#include <input/KeyboardButtonHandler.h>
#include <input/MouseButtonHandler.h>
#include "SpyE.h"
#include <logic/Game.h>
#include <stdio.h>

SpyE::SpyE(Game *game) {
    this->game = game;
    //glm::mat4 trans = glm::scale(entity->getTransformation(), glm::vec3(2.0f, 2.0f, 2.0f));
}

void SpyE::init() {

    /*Use scan codes for mapping keyboard from now on. For full list of scan codes:
    *	check SDL_scancode.h
    *	OR
    *	https://wiki.libsdl.org/SDLScancodeLookup
    */
    game->input->mapButton("Escape", new KeyboardButtonHandler(SDL_SCANCODE_ESCAPE, game->input));
    game->input->mapButton("Left", new KeyboardButtonHandler(SDL_SCANCODE_LEFT, game->input));
    game->input->mapButton("Right", new KeyboardButtonHandler(SDL_SCANCODE_RIGHT, game->input));
    game->input->mapButton("Down", new KeyboardButtonHandler(SDL_SCANCODE_DOWN, game->input));
    game->input->mapButton("Up", new KeyboardButtonHandler(SDL_SCANCODE_UP, game->input));
    game->input->mapButton("W", new KeyboardButtonHandler(SDL_SCANCODE_W, game->input));
    game->input->mapButton("S", new KeyboardButtonHandler(SDL_SCANCODE_S, game->input));

    /*  Use keycodes given below for mouse input:
    *	SDL_BUTTON_LEFT
    *	SDL_BUTTON_RIGHT
    *	SDL_BUTTON_MIDDLE
    *	SDL_BUTTON_X1
    *	SDL_BUTTON_X2
    */
    game->input->mapButton("Left Click", new MouseButtonHandler(SDL_BUTTON_LEFT, game->input));

}

void SpyE::update(float dt) {


    if (game->input->wasReleased("Escape") || game->input->quit)
        game->quit = true;

    if (game->input->justPressed("Left Click"))
        printf("clicked\n");

}


#endif