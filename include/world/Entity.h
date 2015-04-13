

#ifndef _SPYE_ENTITY_H_
#define _SPYE_ENTITY_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>

class Entity {

protected:

public:
    std::string name;
    glm::vec3 position;
    glm::vec3 pivot;
    glm::quat orientation;
    glm::mat4 transformation;
    glm::vec3 color;
    glm::vec3 scale;

    Entity();
    virtual ~Entity() {};
    glm::mat4& getTransformation() {

        transformation = glm::translate(glm::mat4(1.0f), position) * glm::translate(glm::mat4(1.0f), pivot*-1.0f) * glm::toMat4(orientation) * glm::scale(glm::mat4(1.0), scale) * glm::translate(glm::mat4(1.0f), pivot);
       /* transformation[3][0] = position[0];
        transformation[3][1] = position[1];
        transformation[3][2] = position[2];*/
        return transformation;

    }
    void setTransformation(glm::mat4& trans) {
        orientation = glm::normalize(glm::toQuat(trans));
        position = glm::vec3(trans[3]);
    }

    glm::quat getOrientation() const;
    void setOrientation(glm::quat &orientation);

    glm::vec3 getPosition() const;
    void setPosition(glm::vec3 &position);
};

#endif
