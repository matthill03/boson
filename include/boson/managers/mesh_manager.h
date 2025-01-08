#pragma once
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/vector3.h>
#include <assimp/material.h>
#include <assimp/types.h>
#include "assimp/matrix4x4.h"
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/scalar_constants.hpp>

#include <filesystem>
#include <unordered_map>
#include <string>
#include <memory>

#include "boson/mesh.h"

namespace boson {

class MeshManager {
public:
    MeshManager();
    ~MeshManager();

    std::shared_ptr<Mesh> load_cube_mesh();
    std::shared_ptr<Mesh> load_plane_mesh();
    std::shared_ptr<Mesh> load_sphere_mesh(GLint sector_count, GLint stack_count, GLfloat radius, const std::string& name);
    std::shared_ptr<Mesh> load_cylinder_mesh(GLint sector_count, GLfloat radius, GLfloat height, const std::string& name);
    std::shared_ptr<Mesh> load_model_mesh(const std::string& file_path);
    std::shared_ptr<Mesh> get_mesh(const std::string& name);

    void unload_mesh(const std::string& name);
    void clear_meshes();

    glm::mat4 convert_matrix(const aiMatrix4x4& mat);

    std::unordered_map<std::string, std::shared_ptr<Mesh>> get_meshes() const { return m_mesh_map; }

private:
    std::unordered_map<std::string, std::shared_ptr<Mesh>> m_mesh_map = {};

    GLuint m_next_mesh_id = 0;

    std::vector<Vertex> plane_vertices = {
        {{-0.5f, 0.0f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, // Front left
        {{ 0.5f, 0.0f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, // Front right
        {{ 0.5f, 0.0f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, // Back right
        {{-0.5f, 0.0f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, // Back left
    };

    std::vector<GLuint> plane_indicies = {
        0, 3, 2,
        2, 1, 0
    };

    std::vector<Vertex> cube_vertices = {
        // Front face
        // Position                // Normal              // Texture Coord
        {{-0.5f, -0.5f, -0.5f}, {0.0f,  0.0f, -1.0f},  {0.0f, 0.0f}},  // Bottom-left  // 0
        {{ 0.5f, -0.5f, -0.5f}, {0.0f,  0.0f, -1.0f},  {1.0f, 0.0f}},  // Bottom-right // 1
        {{ 0.5f,  0.5f, -0.5f}, {0.0f,  0.0f, -1.0f},  {1.0f, 1.0f}},  // Top-right    // 2
        {{-0.5f,  0.5f, -0.5f}, {0.0f,  0.0f, -1.0f},  {0.0f, 1.0f}},  // Top-left     // 3

        // Back face
        {{ 0.5f, -0.5f,  0.5f}, {0.0f,  0.0f,  1.0f},  {0.0f, 0.0f}},  // Bottom-right // 4
        {{ 0.5f,  0.5f,  0.5f}, {0.0f,  0.0f,  1.0f},  {0.0f, 1.0f}},  // Top-right    // 5
        {{-0.5f,  0.5f,  0.5f}, {0.0f,  0.0f,  1.0f},  {1.0f, 1.0f}},  // Top-left     // 6
        {{-0.5f, -0.5f,  0.5f}, {0.0f,  0.0f,  1.0f},  {1.0f, 0.0f}},  // Bottom-left  // 7

        // Left face
        {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},  // Bottom-front // 8
        {{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},  // Top-front    // 9
        {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},  // Top-back     // 10
        {{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},  // Bottom-back  // 11
// Right face
        {{ 0.5f, -0.5f,  0.5f},  {1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},  // Bottom-back  // 12
        {{ 0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},  // Top-back     // 13
        {{ 0.5f,  0.5f, -0.5f},  {1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},  // Top-front    // 14
        {{ 0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},  // Bottom-front // 15

        // Top face
        {{-0.5f,  0.5f, -0.5f}, {0.0f,  1.0f,  0.0f},  {0.0f, 0.0f}},  // Front-left   // 16
        {{ 0.5f,  0.5f, -0.5f}, {0.0f,  1.0f,  0.0f},  {1.0f, 0.0f}},  // Front-right  // 17
        {{ 0.5f,  0.5f,  0.5f}, {0.0f,  1.0f,  0.0f},  {1.0f, 1.0f}},  // Back-right   // 18
        {{-0.5f,  0.5f,  0.5f}, {0.0f,  1.0f,  0.0f},  {0.0f, 1.0f}},  // Back-left    // 19

        // Bottom face
        {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f,  0.0f},  {0.0f, 0.0f}},  // Back-left    // 20
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f,  0.0f},  {1.0f, 0.0f}},  // Back-right   // 21
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f,  0.0f},  {1.0f, 1.0f}},  // Front-right  // 22
        {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f,  0.0f},  {0.0f, 1.0f}}   // Front-left   // 23
    };

    std::vector<GLuint> cube_indices = {
        // Front face
        2, 1, 0,
        0, 3, 2,

        // Back face
        7, 4, 5,
        5, 6, 7,

        // Left face
        10, 9, 8,
        8, 11, 10,

        // Right face
        14, 13, 12,
        12, 15, 14,

        // Top face
        18, 17, 16,
        16, 19, 18,

        // Bottom face
        22, 21, 20,
        20, 23, 22
    };

    std::shared_ptr<Mesh> process_scene_mesh(const aiNode& child, const aiScene& scene, const std::string& model_root_path);
    void process_node(const std::shared_ptr<Mesh> mesh, const aiNode& node, const aiScene& scene, const std::string& model_root_path, glm::mat4 parent_transform);
};

}
