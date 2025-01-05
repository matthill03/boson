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
    PLANE,
    SPHERE,
    CYLINDER,
    MODEL,
};

typedef struct ObjectInfo {
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 rotation;
    Material material;
} ObjectInfo;

typedef struct CubeInfo {
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 rotation;
    Material material;
} CubeInfo;

typedef struct PlaneInfo {
    glm::vec3 position;
    glm::vec2 size;
    glm::vec3 rotation;
    Material material;
} PlaneInfo;

typedef struct SphereInfo {
    glm::vec3 position;
    GLint sector_count;
    GLint stack_count;
    GLfloat radius;
    glm::vec3 rotation;
    Material material;


} SphereInfo;

typedef struct CylinderInfo {
    glm::vec3 position;
    GLint sector_count;
    GLfloat radius;
    GLfloat height;
    glm::vec3 rotation;
    Material material;


} CylinderInfo;


class Object {
public:
    Object(const ObjectInfo& info);
    ~Object();

    glm::mat4 get_model() const { return m_model_matrix; }
    Material get_material() const { return m_material; }

private:
    glm::mat4 m_model_matrix = glm::mat4(1.0f);
    Material m_material = {
        {0.2f, 0.2f, 0.2f},
        {0.5f, 0.5f, 0.5f},
        {0.8f, 0.8f, 0.8f},
        32
    };
};

}
