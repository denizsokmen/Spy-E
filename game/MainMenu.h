#ifndef MAINMENU_H_INC
#define MAINMENU_H_INC
#include <logic/System.h>

class Game;

class MainMenu : public System {
	Game* game;

public:
	MainMenu(Game* game);
	~MainMenu();
	void init();
	void update(float dt);
	void draw();
	void draw2D();
};


#endif