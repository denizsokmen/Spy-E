#ifndef MAINMENU_H_INC
#define MAINMENU_H_INC
#include <logic/System.h>

class Game;
class Drawable;
class Drawer;

class MainMenu : public System {
	Game* game;

public:
	MainMenu(Game* game, Drawer* drawer);
	~MainMenu();
	void init();
	void update(float dt);
	void draw();
	void draw2D();

	Drawable *gfxMainMenu;
	Drawer *drawer;
};


#endif