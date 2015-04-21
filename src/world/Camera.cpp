
#include "world/Camera.h"

Camera::Camera() {
	safePitch = 0.0f;
}

Camera::~Camera() {

}

void Camera::lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up) {
    view = glm::lookAt(eye, target, up);

}

glm::vec3 Camera::unProject(glm::vec3 windowCoordinate, glm::vec2 windowSize) {
	glm::vec4 viewPort = glm::vec4(0.0f,0.0f,windowSize.x, windowSize.y);
	return glm::unProject(windowCoordinate,
										glm::translate(this->view, this->position),
										this->projection,
										viewPort);

}

void Camera::fpsRotation(float head, float pitch) {
	orientation = glm::quat_cast(view);
	safePitch += pitch;
	if (safePitch > 90.0f) {
		pitch = 90.0f - (safePitch - pitch);
		safePitch = 90.0f;
	}
	if (safePitch < -90.0f) {
		pitch = -90.0f - (safePitch - pitch);
		safePitch = -90.0f;
	}
	glm::quat newRot;
	if (head != 0.0f) {
		newRot = glm::angleAxis(glm::radians(-head), glm::vec3(0.0f, 1.0f, 0.0f));
		orientation = orientation * newRot;
	}
	if (pitch != 0.0f) {
		newRot = glm::angleAxis(glm::radians(-pitch), glm::vec3(1.0f, 0.0f, 0.0f));
		orientation = newRot * orientation;
	}
	orientation = glm::normalize(orientation);
	if (pitch != 0.0f || head != 0.0f) {
		updateView();
	}
}

void Camera::updateView() {
	orientation = glm::normalize(orientation);
	view = glm::mat4_cast(orientation);
	localX = glm::vec3(view[0][0], view[1][0], view[2][0]);
	localY = glm::vec3(view[0][1], view[1][1], view[2][1]);
	localZ = glm::vec3(view[0][2], view[1][2], view[2][2]);
	viewDirection = -localZ;
	view[3][0] = -glm::dot(localX, position);
	view[3][1] = -glm::dot(localY, position);
	view[3][2] = -glm::dot(localZ, position);
}

void Camera::move(float dx, float dy, float dz) {
	position += dx * localX;
	position += dy * localY;
	position += dz * viewDirection;
	updateView();
}