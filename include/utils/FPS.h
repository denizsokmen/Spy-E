
#ifndef _SPYE_FPS_H_
#define _SPYE_FPS_H_

class FPS {

protected:
    unsigned int fps;
    unsigned int fpsCount;
    float fpsInterval;

public:
    FPS() : fps(0), fpsCount(0), fpsInterval(0) { }


    void update(float dt) {
        fpsCount++;
        fpsInterval += dt;

        if (fpsInterval > 1.0f) {
            fps = fpsCount;

            fpsCount = 0;
            fpsInterval = dt;
        }
    }

    unsigned int get()  {
        return fps;
    }
};


#endif //_SPYE_FPS_H_
