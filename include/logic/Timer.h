#ifndef TIMER_H_INC
#define TIMER_H_INC

class Timer {

public:
    Timer(int ticksPerSecond);
    ~Timer();

    bool tick();
    void endLoop();

    int maxUpdate;
    int updateCount;

    double clock;
    double stepClock;

    float getTickSize();
};


#endif