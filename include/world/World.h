
#ifndef __SpyE_World__
#define __SpyE_World__
#include <vector>

class Entity;
class Renderable;
class Cube;
class ObjLoader;

class World {

	private:
		std::vector<Entity *> entities;
		std::vector<Renderable *> renderables;
		ObjLoader *objLoader;


	public:
		World();
		~World();

		int getEntityCount();

		Entity* getEntity(int identifier);
		std::vector<Entity*> getEntities();
		std::vector<Renderable*> getRenderables();
		void addEntity(Entity *entity);
		Renderable* createRenderable(const char* name);
		Cube* createCube();
		void addEntities(std::vector<Entity *> *entities);

		Entity *createEntity();

};


#endif

