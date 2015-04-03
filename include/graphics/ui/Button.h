
#ifndef SPYE_BUTTON_H
#define SPYE_BUTTON_H

#include <graphics/ui/View.h>
#include <functional>

class Button : public View {

protected:
    void runTarget();

private:
    std::function<void()> target;

public:
    Button();

    void setTarget(std::function<void()> target);

};


#endif //SPYE_BUTTON_H
