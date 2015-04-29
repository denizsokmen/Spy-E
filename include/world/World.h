
#ifndef __SpyE_World__
#define __SpyE_World__

#include <vector>
#include <string>
#include <map>

class Entity;
class Renderable;
class ObjLoader;
class Light;

class World {

private:
    std::vector<Entity *> entities;
    std::vector<Renderable *> renderables;
    std::vector<Light *> lights;
    std::map<std::string, Entity*> entityMap;
    ObjLoader *objLoader;

    std::string name;
    std::string version;

public:

    World();
    ~World();
    void update(float dt);


    void addLight(Light *light);


    Entity* getEntity(std::string name);
    Entity *createEntity();

    std::vector<Renderable*>& getRenderables();
    std::vector<Light*>& getLights();

    void addEntity(Entity *entity);

    Renderable *createRenderable(const char *name);
    std::string getName();
    void setName(std::string name);
    std::string getVersion();
    void setVersion(std::string version);
    Renderable *createRenderableFromPath(char const *modelPath);

    void mapEntity(std::string name, Entity *entity);
};


#endif

