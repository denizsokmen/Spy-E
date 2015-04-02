#include "physics/Physics.h"

Physics::Physics(){
    physicsWorld = new PhysicsWorld();
}

Physics::~Physics(){

}

void Physics::update(float dt) {
    physicsWorld->update(dt);
}

PhysicsWorld *Physics::getWorld() {
    return this->physicsWorld;
}
