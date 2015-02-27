#ifndef SCENE_H_INC
#define SCENE_H_INC

class World;
class Camera;
class Renderer;

class Scene {
	Camera* camera;
	World* world;
	Renderer* renderer;


public:
	Scene();
	void render();
	void update();
};

#endif