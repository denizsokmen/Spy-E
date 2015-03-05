#ifndef SCENE_H_INC
#define SCENE_H_INC

#include "System.h"
#include "World.h"
#include <vector>

class World;
class Camera;
class Renderer;
class Renderable;

class Scene : public System {
	Camera* camera;


private:
	World* world;
	Renderer* renderer;

	std::vector<Renderable*> renderList;


public:
	Scene();
	~Scene();
	void draw();
	void update(float dt);

	World *getWorld() const {
		return world;
	}

	void setWorld(World *world) {
		this->world = world;
	}
};

#endif