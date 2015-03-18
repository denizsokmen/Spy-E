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

    void lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
    void perspective(float fov, float ratio, float near, float far) {
        projection = glm::perspective(fov, ratio, near, far);
    }
    void ortho(float left, float right, float top, float bot) {
        projection = glm::ortho(left, right, bot, top);
    }


};