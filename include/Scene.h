#ifndef SCENE_H_INC
#define SCENE_H_INC

#include "System.h"

class World;
class Camera;
class Renderer;

class Scene : public System {
	Camera* camera;
	World* world;
	Renderer* renderer;


public:
	Scene();
	~Scene();
	void draw();
	void update(float dt);
};

#endif