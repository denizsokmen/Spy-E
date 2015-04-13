#ifndef MAINMENU_H_INC
#define MAINMENU_H_INC
#include <logic/System.h>

class Game;
class Drawer;

class MainMenu : public System {
	Game* game;

public:
	MainMenu(Game* game);
	~MainMenu();
	void init();
	void update(float dt);
	void draw();
	void draw2D();
	bool active;


	Drawer *drawer;
};


#endif