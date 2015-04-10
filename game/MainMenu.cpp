#include "MainMenu.h"
#include <logic/Game.h>
#include <graphics/Texture.h>
#include <SDL_image.h>
#include <graphics/Drawable.h>
#include <graphics/Drawer.h>
#include <glm/glm.hpp>

MainMenu::MainMenu(Game *game, Drawer* drawer) {
	this->game = game;
	active = true;
}


MainMenu::~MainMenu() {

}

void MainMenu::init() {
	this->drawer = game->drawer;
	gfxMainMenu = drawer->createDrawable("assets/texture/menu/menu.png");

}

void MainMenu::draw() {

}

void MainMenu::draw2D() {
	if (!active)
		return;
	if (drawer != NULL)
	drawer->draw(gfxMainMenu, glm::vec2(0,0), glm::vec2(gfxMainMenu->texture->width, gfxMainMenu->texture->height));
}

void MainMenu::update(float dt) {

}

