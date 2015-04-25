#ifndef __Agile__Renderable__
#define __Agile__Renderable__

#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "world/Entity.h"
#include <vector>
#include <string>

class VertexBuffer;
class Mesh;
class Renderer;
class Animation;

class Renderable : public Entity {

protected:


public:
    Renderable();
    Mesh* mesh;
	Animation* animation;

    unsigned int identifier;

    ~Renderable();
    virtual void render(Renderer *renderer);
	void update(float dt);

	void addAnimation(std::string name, std::string filename);
	void setAnimation(std::string name);
//    void load(); FIXME: Someone should make a decision whether to keep them or delete them.
//    void unload();

	std::vector<glm::mat4> boneMatrix;

    VertexBuffer* getVertexBuffer();



};


#endif /* defined(__Agile__Renderable__) */
