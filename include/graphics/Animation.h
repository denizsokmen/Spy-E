//
// Created by Deniz Sokmen on 24/04/15.
//

#ifndef SPYE_ANIMATION_H
#define SPYE_ANIMATION_H
#include <vector>
#include <map>
#include <string>


class AnimationState;

class Animation {

public:
    void update(float dt);

    std::vector<AnimationState*> states;
    //running walking
    std::map<std::string, AnimationState*> namedStates;
};
#endif //SPYE_ANIMATION_H
