#ifndef SYSCTL_H_INC
#define SYSCTL_H_INC
#include <map>
#include <vector>
#include <string>

class System;

class SystemController {

    /*input physics scene sound ai*/
    std::vector<System*> coreSystems;

    /* gameStates["mainmenu"]
       gameStates["ingame"]
       gameStates["pause"]
     */
    std::map<std::string, std::vector<System*>> gameStates;
    std::vector<System*>* currentState;
    std::string currentStateName;

public:
    SystemController();
    ~SystemController();

    void update(float dt);
    void draw();

    /* begin(), end() ? */

};

#endif