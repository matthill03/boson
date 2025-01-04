#pragma once
#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <unordered_map>
#include <vector>

#include "boson/vertex_array.h"
#include "boson/object.h"
#include "boson/shader.h"

namespace boson {

class Renderer {
public:
    Renderer(const Shader& shader);
    ~Renderer();

    void add_obj(const Object& obj);

    void draw();

private:
    std::unordered_map<ObjectType, std::unique_ptr<VertexArray>> m_vertex_arrays = {};
    std::unordered_map<GLuint, std::vector<glm::mat4>> m_obj_data = {};

    std::unique_ptr<Shader> m_shader = nullptr;

    glm::mat4 m_proj_matrix = glm::perspective(glm::radians(45.0f), (float)1080 / (float)720, 0.1f, 100.0f);
    glm::mat4 m_view_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));

    std::vector<GLfloat> square_vertices = {
        // Front face
        // Position                // Normal              // Texture Coord
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,    0.0f, 0.0f,  // Bottom-left  // 0
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,    1.0f, 0.0f,  // Bottom-right // 1
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,    1.0f, 1.0f,  // Top-right    // 2
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,    0.0f, 1.0f,  // Top-left     // 3

        // Back face
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,    0.0f, 0.0f,  // Bottom-right // 4
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,    0.0f, 1.0f,  // Top-right    // 5
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,    1.0f, 1.0f,  // Top-left     // 6
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,    1.0f, 0.0f,  // Bottom-left  // 7

        // Left face
        -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,  // Bottom-front // 8
        -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,  // Top-front    // 9
        -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,  // Top-back     // 10
        -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,  // Bottom-back  // 11

        // Right face
         0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,  // Bottom-back  // 12
         0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,  // Top-back     // 13
         0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,  // Top-front    // 14
         0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,  // Bottom-front // 15

        // Top face
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,    0.0f, 0.0f,  // Front-left   // 16
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,    1.0f, 0.0f,  // Front-right  // 17
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,    1.0f, 1.0f,  // Back-right   // 18
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,    0.0f, 1.0f,  // Back-left    // 19

        // Bottom face
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,    0.0f, 0.0f,  // Back-left    // 20
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,    1.0f, 0.0f,  // Back-right   // 21
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,    1.0f, 1.0f,  // Front-right  // 22
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,    0.0f, 1.0f   // Front-left  // 23    
    };

    std::vector<GLuint> square_indices = {
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Back face
        5, 4, 7,
        7, 6, 5,

        // Left face
        8, 9, 10,
        10, 11, 8,

        // Right face
        12, 13, 14,
        14, 15, 12,

        // Top face
        16, 17, 18,
        18, 19, 16,

        // Bottom face
        20, 21, 22,
        22, 23, 20
    };

};

}
