#ifndef PHYSICS_H_INC
#define PHYSICS_H_INC

#include <vector>
#include "System.h"

class Physics : public System {

public:
    Physics();
    ~Physics();

    void update(float dt);

};

#endif