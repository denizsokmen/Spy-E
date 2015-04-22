#include "logic/SystemController.h"
#include "logic/System.h"

SystemController::SystemController() {
    currentState = NULL;
}

SystemController::~SystemController() {
}

void SystemController::update(float dt) {
    for (auto system: coreSystems) {
        system->update(dt);
    }

    if (currentState != NULL) {
        for (auto system: *currentState) {
            system->update(dt);
        }
    }
}

void SystemController::init() {
    for (auto system: coreSystems) {
        system->init();
    }

    if (currentState != NULL) {
        for (auto system: *currentState) {
            system->init();
        }
    }
}

void SystemController::draw() {
    for (auto system: coreSystems) {
        system->draw();
    }

    if (currentState != NULL) {
        for (auto system: *currentState) {
            system->draw();
        }
    }
}

void SystemController::draw2D() {
    for (auto system: coreSystems) {
        system->draw2D();
    }

    if (currentState != NULL) {
        for (auto system: *currentState) {
            system->draw2D();
        }
    }
}

void SystemController::setState(std::string name) {
    std::map<std::string, std::vector<System*>>::iterator state = gameStates.find(name);
    if (state != gameStates.end()) {
		
        currentState = &state->second;

		
    }
}

void SystemController::addState(std::string name) {
	gameStates.insert(std::map<std::string, std::vector<System*>>::value_type(name, std::vector<System*>()));
}

void SystemController::addCoreSystem(System *s) {
    coreSystems.push_back(s);
}

void SystemController::addSystem(std::string state, System *s) {
	std::map<std::string, std::vector<System*>>::iterator res = gameStates.find(state);
	if (res != gameStates.end()) {
		res->second.push_back(s);
	}
	else {
		printf("State not found: %s\n", state.c_str());
	}
}

