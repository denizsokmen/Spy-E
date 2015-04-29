//
// Created by deniz on 29/04/15.
//
#ifndef SPYE_LIGHT_H
#define SPYE_LIGHT_H
#include "Entity.h"

enum LightType {
    LIGHT_DIRECTIONAL = 0,
    LIGHT_SPOT,
    LIGHT_POINT
};


class Light: public Entity {


public:
    Light();
    ~Light();
    glm::vec3 intensities; //color
    glm::vec3 coneDirection;
    float ambientCoefficient;
    float attenuation;
    float coneAngle;
    LightType type;
};

#endif //SPYE_LIGHT_H
