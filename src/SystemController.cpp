#include "SystemController.h"

SystemController::SystemController() {
}

SystemController::~SystemController() {
}

void SystemController::update(float dt) {
}

void SystemController::draw() {
}

void SystemController::addCoreSystem(System *s) {
    coreSystems.push_back(s);
}

