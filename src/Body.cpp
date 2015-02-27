#include "Body.h"

Body::Body(glm::vec3 loc, glm::vec3 s, glm::vec3 acc){

    location = loc;
    speed = s;
    acceleration = acc;
}

Body::~Body(){

}