#ifndef RAYCALLBACK_H_INC
#define RAYCALLBACK_H_INC

class Body;

class RayCallback {
public:
	RayCallback();
	void onHit(Body* target);

};

#endif