#include "MainMenu.h"
#include <logic/Game.h>
#include <graphics/Texture.h>
#include <SDL_image.h>
#include <graphics/Drawable.h>
#include <graphics/Drawer.h>
#include <glm/glm.hpp>

MainMenu::MainMenu(Game *game, Drawer* drawer) {
	this->game = game;
}


MainMenu::~MainMenu() {

}

void MainMenu::init() {
	this->drawer = game->drawer;
	gfxMainMenu = drawer->createDrawable("assets/texture/menu/background.png");

}

void MainMenu::draw() {

}

void MainMenu::draw2D() {
	drawer->draw(gfxMainMenu, glm::vec2(game->width/2, game->height/2), glm::vec2(gfxMainMenu->texture->width, gfxMainMenu->texture->height));
}

void MainMenu::update(float dt) {

}

