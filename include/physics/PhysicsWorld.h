#ifndef PHYSICSWORLD_H_INC
#define PHYSICSWORLD_H_INC
#include <vector>
#include "Body.h"

class PhysicsWorld{

    std::vector<Body*> bodies;

public:
    PhysicsWorld();
    ~PhysicsWorld();

    Body* createBody(glm::vec3 loc, glm::vec3 speed, glm::vec3 acc);
    void update(float dt);
    bool isCollided(Body *b1, Body *b2);
};
#endif