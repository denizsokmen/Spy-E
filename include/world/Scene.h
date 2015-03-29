#ifndef SCENE_H_INC
#define SCENE_H_INC

#include "logic/System.h"
#include "world/World.h"
#include <vector>

class World;
class Camera;
class Renderer;
class Renderable;

class Scene : public System {


private:
	World* world;
	Renderer* renderer;

	std::vector<Renderable*> renderList;


public:
	Camera* camera;
	Scene();
	~Scene();
	void draw();
	void update(float dt);

	void init() {}

	World *getWorld() const {
		return world;
	}

	void setWorld(World *world) {
		this->world = world;
	}
};

#endif