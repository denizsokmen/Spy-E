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
    bool castRay(glm::vec3 ray_origin,        //Ray origin, in world space
                 glm::vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
                 glm::vec3 aabb_min,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
                 glm::vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
                 glm::mat4 ModelMatrix,       // Transformation applied to the mesh (which will thus be also applied to its bounding box)
                 float& intersection_distance);
};

#endif