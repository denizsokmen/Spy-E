#include "Timer.h"
#include <glfw3.h>
#include <stdio.h>
#include "SDL.h"

Timer::Timer(int ticksPerSecond) {

    maxUpdate = ticksPerSecond;
    updateCount = 0;
    stepClock = 1000.0/((double)ticksPerSecond);
    clock = 0.0;
}

Timer::~Timer() {

}

bool Timer::tick() {
    if (++updateCount > maxUpdate)
        return false;

    if (clock < (double)SDL_GetTicks()) {
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

float Timer::getTickSize() {
    return ((float)stepClock)/1000.0f;
}
