#ifndef SYSTEM_H_INC
#define SYSTEM_H_INC

class System {

public:
    System();
    ~System();

    void update(float dt);
    void draw();
};

#endif