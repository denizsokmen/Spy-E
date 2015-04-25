//
// Created by Deniz Sokmen on 25/04/15.
//

#include <graphics/AnimationState.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

void AnimationState::interpolateSkeletons(Skeleton &finalskel, Skeleton &sk0, Skeleton &sk1, float intrp) {
    //Most important part of the animation is to
    //interpolate between two skeletons(frames) to
    //get smoother final skeleton.
    for (int i=0; i < numJoints; i++) {

        Bone& finalBone = finalskel.bones[i];
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
       // boneMatrix[i] = translation * rotation;
    }
}

void AnimationState::update(float deltaTime) {
    animTime += deltaTime;
    while (animTime > animDuration) animTime -= animDuration;
    while (animTime < 0.0f ) animTime += animDuration;

    float frameNum = animTime * (float) frameRate;
    int frame0 = (int) floorf( frameNum );
    int frame1 = (int) ceilf( frameNum );
    frame0 %= numFrames;
    frame1 %= numFrames;

    float intrp = fmodf(animTime, frameDuration);
    interpolateSkeletons(currentSkeleton, frameSkeleton[frame0],
                         frameSkeleton[frame1], intrp);
}

AnimationState::AnimationState() {

}

AnimationState::~AnimationState() {

}
