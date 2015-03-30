//
// Created by deniz on 27/03/15.
//

#include "InputState.h"
#include "SpyE.h"
#include <logic/Game.h>
#include <input/Input.h>
#include <input/KeyboardButtonHandler.h>
#include <input/MouseButtonHandler.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "MainMenu.h"
#include <graphics/Renderable.h>

void InputState::init() {
    game->input->mapButton("Escape", new KeyboardButtonHandler(SDL_SCANCODE_ESCAPE, game->input));
    game->input->mapButton("Left", new KeyboardButtonHandler(SDL_SCANCODE_LEFT, game->input));
    game->input->mapButton("Right", new KeyboardButtonHandler(SDL_SCANCODE_RIGHT, game->input));
    game->input->mapButton("Down", new KeyboardButtonHandler(SDL_SCANCODE_DOWN, game->input));
    game->input->mapButton("Up", new KeyboardButtonHandler(SDL_SCANCODE_UP, game->input));
    game->input->mapButton("W", new KeyboardButtonHandler(SDL_SCANCODE_W, game->input));
    game->input->mapButton("S", new KeyboardButtonHandler(SDL_SCANCODE_S, game->input));
    game->input->mapButton("Enter", new KeyboardButtonHandler(SDL_SCANCODE_RETURN, game->input));

    /*  Use keycodes given below for mouse input:
    *	SDL_BUTTON_LEFT
    *	SDL_BUTTON_RIGHT
    *	SDL_BUTTON_MIDDLE
    *	SDL_BUTTON_X1
    *	SDL_BUTTON_X2
    */
    game->input->mapButton("Left Click", new MouseButtonHandler(SDL_BUTTON_LEFT, game->input));

}

void InputState::update(float dt) {


    if (game->input->wasReleased("Escape") || game->input->quit)
        game->quit = true;

    if (currentState == STATE_GAME) {
        Entity* entity = spye->entity;
        if (game->input->isPressed("Left")) {
            entity->orientation = glm::rotate(entity->orientation, 90.0f * dt, glm::vec3(0.0f, 1.0f, 0.0f));
        }

        if (game->input->isPressed("Right")) {
            entity->orientation = glm::rotate(entity->orientation, 90.0f * dt, glm::vec3(0.0f, -1.0f, 0.0f));
        }



        if (game->input->isPressed("Up")) {
            glm::vec3 forward = glm::normalize(entity->orientation * glm::vec3(0.0f, 0.0f, -1.0f));
            entity->position += forward * 10.0f * dt;
        }

        if (game->input->isPressed("Down")) {
            glm::vec3 back = glm::normalize(entity->orientation * glm::vec3(0.0f, 0.0f, 1.0f));
            entity->position += back * 10.0f * dt;
        }
    }
    else if(currentState == STATE_MAINMENU) {
        if (game->input->isPressed("Enter")) {
            currentState = STATE_GAME;
            mainmenu->active=false;
            spye->activate();
        }
    }


}

void InputState::draw() {

}

void InputState::draw2D() {

}

InputState::InputState(Game* game, SpyE* spye, MainMenu* mainmenu) {
    currentState = STATE_MAINMENU;
    this->game = game;
    this->mainmenu = mainmenu;
    this->spye = spye;
}

InputState::~InputState() {

}
