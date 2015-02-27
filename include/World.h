
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
		void addEntity(Entity *entity);
		void addEntities(std::vector<Entity *> *entities);

};


#endif

