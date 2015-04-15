
#ifndef __SpyE_World__
#define __SpyE_World__

#include <vector>
#include <string>

class Entity;
class Renderable;
class ObjLoader;

class World {

	private:
		std::vector<Entity *> entities;
		std::vector<Renderable *> renderables;
		ObjLoader *objLoader;
	std::string name;
	std::string version;

	public:
		World();
		~World();

		int getEntityCount();

		Entity* getEntity(int identifier);

	Entity *createEntity();

		std::vector<Entity*>& getEntities();
		std::vector<Renderable*>& getRenderables();
		void addEntity(Entity *entity);
		void addEntities(std::vector<Entity *> *entities);

	Renderable *createRenderable(const char *name);

	std::string getName();

	void setName(std::string name);

	std::string getVersion();

	void setVersion(std::string version);


};


#endif

