#pragma once
#include "GL/glew.h"
#include <glm/glm.hpp>

#include <memory>
#include <unordered_map>
#include <vector>

#include "boson/vertex_array.h"
#include "boson/object.h"
#include "boson/shader.h"

namespace boson {

enum class RendererType {
    SQUARE,
    NONE,
};

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

    //std::vector<glm::mat4> m_object_matrices = {};

    std::vector<GLfloat> square_vertices = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };

    std::vector<GLuint> square_indices = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

};

}
