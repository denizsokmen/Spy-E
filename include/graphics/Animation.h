//
// Created by Deniz Sokmen on 24/04/15.
//

#ifndef SPYE_ANIMATION_H
#define SPYE_ANIMATION_H
#include <vector>
#include <map>
#include <string>
#include <graphics/Skeleton.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


class AnimationState;


class Animation {

public:
	Animation();
	~Animation();
    void update(float dt);

	Skeleton currentSkeleton;

    //running walking
    std::map<std::string, AnimationState*> namedStates;
	AnimationState* currentState;

	float animTime;


	std::vector<glm::mat4> boneMatrix;

	void setState(std::string name);
	void addState(std::string name, AnimationState* state);
};
#endif //SPYE_ANIMATION_H
