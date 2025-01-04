#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace boson {

enum class ObjectType {
    CUBE,
};

typedef struct {
    ObjectType type;
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 rotation;
    glm::vec3 colour;
} ObjectInfo;

class Object {
public:
    Object(const ObjectInfo& info);
    ~Object();

    ObjectType get_type() const { return m_type; }
    glm::mat4 get_model() const { return m_model_matrix; }

private:
    ObjectType m_type;
    glm::mat4 m_model_matrix = glm::mat4(1.0f);
};

}
