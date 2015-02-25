#ifndef SCENE_H_INC
#define SCENE_H_INC

class World;
class Camera;

class Scene {
	Camera* camera;
	World* world;

public:
	Scene();
	void render();
};

#endif