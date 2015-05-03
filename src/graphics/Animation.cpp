//
// Created by Deniz Sokmen on 25/04/15.
//

#include <graphics/Animation.h>
#include <graphics/AnimationState.h>


Animation::Animation() {
	currentState = NULL;
	animTime = 0.0f;
	boneMatrix.resize(150, glm::mat4(1.0f));
}

Animation::~Animation() {

}

void Animation::setState(std::string name) {
	auto it = namedStates.find(name);
	if (it != namedStates.end()) {
		if (currentState != it->second) {
			currentState = it->second;
			currentSkeleton = currentState->baseSkeleton;
			animTime = 0.0f;
		}
	}
}

void Animation::addState(std::string name, AnimationState* state) {
	namedStates[name] = state;
}

void Animation::update(float dt) {
	if (!currentState)
		return;

	animTime += dt;
	while (animTime > currentState->animDuration) animTime -= currentState->animDuration;
	while (animTime < 0.0f) animTime += currentState->animDuration;

	float frameNum = animTime * (float)currentState->frameRate;
	int frame0 = (int)floorf(frameNum);
	int frame1 = (int)ceilf(frameNum);
	frame0 %= currentState->numFrames;
	frame1 %= currentState->numFrames;

	float intrp = fmodf(animTime, currentState->frameDuration);

	Skeleton& sk0 = currentState->frameSkeleton[frame0];
	Skeleton& sk1 = currentState->frameSkeleton[frame1];
	

	for (int i = 0; i < currentState->numJoints; i++) {

		Bone& finalBone = currentSkeleton.bones[i];
		Bone& bone0 = sk0.bones[i];
		Bone& bone1 = sk1.bones[i];

		finalBone.parentID = bone0.parentID;
	

		//Linear and spherical interpolation.
		finalBone.worldPos = bone0.worldPos + (bone1.worldPos - bone0.worldPos)* intrp;
		finalBone.worldRotation = glm::slerp(bone0.worldRotation, bone1.worldRotation, intrp);



		glm::mat4 translation = glm::translate(glm::mat4(1.0f), finalBone.worldPos);
		glm::mat4 rotation = glm::toMat4(finalBone.worldRotation);
		//This is what we need, to calculate offset matrices
		//so we can upload them to GPU and transform the vertices.
		boneMatrix[i] = translation * rotation;
	
	}


}