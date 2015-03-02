
#ifndef __SpyE_World__
#define __SpyE_World__
#include <vector>

class Entity;


class World {

	private:
		std::vector<Entity *> entities;


	public:
		int getEntityCount();

		Entity* getEntity(int identifier);
		std::vector<Entity*> getEntities();
		void addEntity(Entity *entity);
		void addEntities(std::vector<Entity *> *entities);

	Entity *createEntity();
};


#endif

