//
// Created by Deniz Sokmen on 24/04/15.
//

#ifndef SPYE_ANIMATIONSTATE_H
#define SPYE_ANIMATIONSTATE_H


#include "Skeleton.h"

//running walking bilmemneying
class AnimationState {


    //2spooky4me
    Skeleton baseSkeleton;
    //Interpolated, current frame.
    Skeleton currentSkeleton;
    //Skeletons of all frames.
    std::vector<Skeleton> frameSkeleton;

    int animatedParts;
    int frameRate;
    int numFrames;
    int numJoints;

    float animTime;
    float animDuration;
    float frameDuration;
};
#endif //SPYE_ANIMATIONSTATE_H
