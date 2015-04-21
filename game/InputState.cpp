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
#include <graphics/ui/Menu.h>
#include <graphics/ui/Button.h>

#include "graphics/ui/GUI.h"
#include "sound/Sounds.h"

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
    

    if (currentState == STATE_GAME) {
        Entity* entity = spye->entity;
        if (game->input->isPressed("Left")) {
            entity->setOrientation(glm::rotate(entity->getOrientation(), 90.0f * dt, glm::vec3(0.0f, 1.0f, 0.0f)));
        }

        if (game->input->isPressed("Right")) {
			entity->setOrientation(glm::rotate(entity->getOrientation(), 90.0f * dt, glm::vec3(0.0f, -1.0f, 0.0f)));
        }

        if (game->input->isPressed("Up")) {
			glm::vec3 forward = glm::normalize(entity->getOrientation() * glm::vec3(0.0f, 0.0f, -1.0f));
			glm::vec3 pos = entity->getPosition() + (forward * 10.0f * dt);
			entity->setPosition(pos);
        }

        if (game->input->isPressed("Down")) {
			glm::vec3 back = glm::normalize(entity->getOrientation() * glm::vec3(0.0f, 0.0f, 1.0f));
			glm::vec3 pos = entity->getPosition() + (back * 10.0f * dt);
			entity->setPosition(pos);
        }


        if (game->input->wasReleased("Escape")) {

            Menu* menu = (Menu*) game->gui->viewWithTag("menu");

            menu->hidden = false;
            mainmenu->active=true;

            currentState = STATE_MAINMENU;



        }

    }
    else if(currentState == STATE_MAINMENU) {
        Menu* menu = (Menu*) game->gui->viewWithTag("menu");

        if (game->input->wasReleased("Escape")) {

            if (spye->active) {
                menu->hidden = true;
                mainmenu->active=false;
                currentState = STATE_GAME;
            }


        }

        if (game->input->isPressed("Enter")) {

            if (menu->getSelectedItem()->getTag() == "start") {
                if (!spye->active) {
                    menu->hidden = true;
                    currentState = STATE_GAME;
                    mainmenu->active=false;
                    spye->activate();
                    Button* startButton = menu->getItem(0);
                    startButton->setText(L"Resume", ControlState::Selected);
                    startButton->setText(L"> Resume", ControlState::Normal);
                }
                else {
                    menu->hidden = true;
                    mainmenu->active=false;
                    currentState = STATE_GAME;
                }

            }
            else {
                menu->getSelectedItem()->runTarget();
            }

        }
        if (game->input->wasReleased("Up")) {
            menu->moveCursorUp();
            game->sounds->play("select");
        }

        if (game->input->wasReleased("Down")) {
            menu->moveCursorDown();
            game->sounds->play("select");
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
