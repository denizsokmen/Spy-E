#ifndef SYSTEM_H_INC
#define SYSTEM_H_INC

class System {

public:
    System() {}

    virtual void update(float dt) {}
    virtual void draw() {}
};

#endif