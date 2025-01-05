#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace boson {

typedef struct {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    GLfloat shininess;

} Material;

enum class ObjectType {
    CUBE,
    MODEL,
};

typedef struct {
    ObjectType type;
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 rotation;
    Material material;
} ObjectInfo;

class Object {
public:
    Object(const ObjectInfo& info);
    ~Object();

    ObjectType get_type() const { return m_type; }
    glm::mat4 get_model() const { return m_model_matrix; }
    Material get_material() const { return m_material; }

private:
    ObjectType m_type;
    glm::mat4 m_model_matrix = glm::mat4(1.0f);
    Material m_material = {
        {0.2f, 0.2f, 0.2f},
        {0.5f, 0.5f, 0.5f},
        {0.8f, 0.8f, 0.8f},
        32
    };
};

}
