

#ifndef __SpyE_Entity__
#define __SpyE_Entity___

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


class Entity {

protected:

    glm::vec3 position;
    glm::quat orientation;

public:

    Entity();
    glm::mat4& getTransformation() { glm::translate(glm::toMat4(orientation),position); }
    void setTransformation(glm::mat4& trans) {
        orientation = glm::toQuat(trans);
        position = glm::vec3(trans[3]);
    }

};

#endif
