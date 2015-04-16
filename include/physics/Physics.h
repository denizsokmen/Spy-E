#ifndef PHYSICS_H_INC
#define PHYSICS_H_INC

#include <vector>
#include "logic/System.h"
#include "PhysicsWorld.h"
#include "include/physics/Body.h"

class Body;
class PhysicsWorld;

class Physics : public System {

private:
    PhysicsWorld* physicsWorld;

public:
    Physics();
    ~Physics();
    void update(float dt);
    PhysicsWorld* getWorld();

    bool castRay(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3 aabbMin, glm::vec3 aabbMax, glm::mat4 modelMatrix,
                 float &intersection_distance);

    bool castRay(glm::vec3 rayOrigin, glm::vec3 rayDirection, Body *body, float& intersectionDistance);

    static glm::vec3 lerp(glm::vec3 A, glm::vec3 B, float t);
    Body *getNearestBody(glm::vec3 rayOrigin, glm::vec3 rayDirection);
};

#endif