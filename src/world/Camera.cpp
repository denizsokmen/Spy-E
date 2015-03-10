
#include "world/Camera.h"

Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up) {
    view = glm::lookAt(eye, target, up);

}
