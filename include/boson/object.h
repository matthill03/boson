#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <vector>
#include <optional>

#include "boson/texture.h"
#include "boson/mesh.h"

namespace boson {

enum class ObjectType {
    CUBE,
    PLANE,
    SPHERE,
    CYLINDER,
    MODEL,
};

typedef struct ObjectInfoMat {
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 rotation;
    Material material;
} ObjectInfoMat;

typedef struct ObjectInfoTex {
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 rotation;
    std::vector<Texture> textures;
    GLfloat shininess;
} ObjectInfoTex;

typedef struct ModelInfo {
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 rotation;
    std::optional<Material> material;
    std::string file_path;
} ModelInfo;

typedef struct CubeInfo {
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 rotation;
    std::optional<Material> material;
    //std::vector<Texture> textures;
    GLfloat shininess;
} CubeInfo;

typedef struct PlaneInfo {
    glm::vec3 position;
    glm::vec2 size;
    glm::vec3 rotation;
    std::optional<Material> material;
    std::optional<GLfloat> tile_count_x;
    std::optional<GLfloat> tile_count_y;
    //std::vector<Texture> textures;
} PlaneInfo;

typedef struct SphereInfo {
    glm::vec3 position;
    GLint sector_count;
    GLint stack_count;
    GLfloat radius;
    glm::vec3 rotation;
    std::vector<Texture> textures;
    Material material;


} SphereInfo;

typedef struct CylinderInfo {
    glm::vec3 position;
    GLint sector_count;
    GLfloat radius;
    GLfloat height;
    glm::vec3 rotation;
    std::vector<Texture> textures;
    Material material;


} CylinderInfo;


class Object {
public:
    Object(const ObjectInfoMat& info);
    Object(const ObjectInfoTex& info);
    ~Object();

    glm::mat4 get_model() const { return m_model_matrix; }
    Material get_material() const { return m_material; }
    GLfloat get_shininess() const { return m_shininess; }

    std::vector<Texture> get_textures() const { return m_textures; }

private:
    glm::mat4 m_model_matrix = glm::mat4(1.0f);
    GLfloat m_shininess = 1.0f;

    Material m_material = {};
    std::vector<Texture> m_textures = {};
};

}
