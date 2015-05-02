#ifndef CAMERA_H_INC
#define CAMERA_H_INC

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

public:
    Camera();
    ~Camera();

    glm::quat orientation;
    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 position;
    glm::vec3 viewDirection; //FIXME: NOT USED (sadtroll)

    glm::vec3 focus;

	glm::vec3 localX;
	glm::vec3 localY;
	glm::vec3 localZ;

	float safePitch;

    void lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
	void perspective(float fov, float ratio, float near, float far);

	void ortho(float left, float right, float top, float bot);


	void fpsRotation(float head, float pitch);
	void move(float dx, float dy, float dz);
	void updateView();


    glm::vec3 unProject(glm::vec3 windowCoordinate, glm::vec2 windowSize);
};

#endif