#include "Timer.h"
#include <glfw3.h>
#include <stdio.h>

Timer::Timer(int ticksPerSecond) {

    maxUpdate = ticksPerSecond;
    updateCount = 0;
    stepClock = 1.0/((double)ticksPerSecond);
    clock = 0.0;
}

Timer::~Timer() {

}

bool Timer::tick() {
    if (++updateCount > maxUpdate)
        return false;

    if (clock < glfwGetTime()) {
        clock += stepClock;
        return true;
    }


    return false;
}

void Timer::endLoop() {
    if (updateCount > maxUpdate)
        clock = glfwGetTime();

    updateCount = 0;
}

