#ifndef SYSTEM_H_INC
#define SYSTEM_H_INC

class System {

public:
    System() {}
	virtual void init() {}
	virtual void update(float dt) {}
	virtual void draw() {}
	virtual void draw2D() {}
	virtual void setActive(bool isActive) {}
};

#endif