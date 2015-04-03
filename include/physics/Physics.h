#ifndef PHYSICS_H_INC
#define PHYSICS_H_INC

#include <vector>
#include "logic/System.h"
#include "PhysicsWorld.h"

class PhysicsWorld;

class Physics : public System {

private:
    PhysicsWorld* physicsWorld;

public:
    Physics();
    ~Physics();
    void update(float dt);
    PhysicsWorld* getWorld();

};

#endif