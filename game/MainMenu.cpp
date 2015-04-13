#include "MainMenu.h"
#include <logic/Game.h>
#include <graphics/ui/GUI.h>
#include <graphics/Drawer.h>
#include <glm/glm.hpp>
#include <graphics/ui/Menu.h>
#include <graphics/ui/Button.h>
#include "graphics/ui/Image.h"
#include "sound/Sounds.h"

MainMenu::MainMenu(Game *game) {
	this->game = game;
	active = true;
}


MainMenu::~MainMenu() {

}

void MainMenu::init() {
	this->drawer = game->drawer;


	Image *image = new Image("./assets/texture/menu/logo.png");
	image->setFrame(Rect(game->width/2-105, 37.5, 210, 37.5));
	game->gui->addSubview(image);

	Menu* menu = new Menu();
	menu->setTag("menu");
	menu->setFrame(Rect(40,game->height/2, 300, 300));


	Button* startButton = new Button();
	startButton->setText(L"Start", Normal);
	startButton->setText(L"> Start", Selected);
	startButton->setTag("start");

	Button* optionsButton = new Button();
	optionsButton->setText(L"Options", Normal);
	optionsButton->setText(L"> Options", Selected);
	optionsButton->setTag("options");
	Button* extraButton = new Button();
	extraButton->setText(L"Extras", Normal);
	extraButton->setText(L"> Extras", Selected);

	Button* exitButton= new Button();
	exitButton->setText(L"Exit", Normal);
	exitButton->setText(L"> Exit", Selected);
	exitButton->setTag("exit");
	exitButton->setTarget(
			[this](){
				this->game->quit = true;
			}
	);
	menu->addItem(startButton);
	menu->addItem(optionsButton);
	menu->addItem(extraButton);
	menu->addItem(exitButton);
	menu->setVerticalSpace(16);
	game->gui->addSubview(menu);

	game->sounds->open("select", "assets/sounds/select.wav");
	game->sounds->open("start", "assets/sounds/start.wav");



}

void MainMenu::draw() {

}

void MainMenu::draw2D() {
	if (!active)
		return;


}



void MainMenu::update(float dt) {

}

