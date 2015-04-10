//
// Created by Deniz Sokmen on 10/04/15.
//

#ifndef SPYE_PLAYER_H
#define SPYE_PLAYER_H

#include <functional>
#include <logic/System.h>

class Renderable;
class Body;


class Player : public System {

    int hp; // gibi gibi ozellikler
public:
    Player();
    ~Player();

    Renderable* meshEntity;
    Body* body;
    std::function<void(Body*)> collisionCallback;



    virtual void init() {}
    virtual void update(float dt) {}
    virtual void draw() {}
    virtual void draw2D() {}

};


#endif //SPYE_PLAYER_H
