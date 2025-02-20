#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <optional>

#include "boson/managers/mesh_manager.h"

namespace boson {

enum class ObjectType {
    CUBE,
    PLANE,
    SPHERE,
    CYLINDER,
    MODEL,
};

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
    GLfloat shininess;
} CubeInfo;

typedef struct PlaneInfo {
    glm::vec3 position;
    glm::vec2 size;
    glm::vec3 rotation;
    std::optional<Material> material;
    std::optional<GLfloat> tile_count_x;
    std::optional<GLfloat> tile_count_y;
} PlaneInfo;

typedef struct SphereInfo {
    glm::vec3 position;
    GLint sector_count;
    GLint stack_count;
    GLfloat radius;
    glm::vec3 rotation;
    std::optional<Material> material;
} SphereInfo;

typedef struct CylinderInfo {
    glm::vec3 position;
    GLint sector_count;
    GLfloat radius;
    GLfloat height;
    glm::vec3 rotation;
    std::optional<Material> material;
} CylinderInfo;



glm::mat4 calculate_transform(glm::vec3 position, glm::vec3 size, glm::vec3 rotation);

void load_model(const ModelInfo& info, MeshManager* mesh_manager);
void load_cube(const CubeInfo& info, MeshManager* mesh_manager);
void load_plane(const PlaneInfo& info, MeshManager* mesh_manager);
void load_sphere(const SphereInfo& info, MeshManager* mesh_manager);
void load_cylinder(const CylinderInfo& info, MeshManager* mesh_manager);



}
