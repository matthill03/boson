#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <vector>

#include <iostream>

namespace boson {

typedef struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coord;
} Vertex;

typedef struct InstanceData {
    glm::mat4 transform;
    GLint material_index;
} InstanceData;

class VertexArray {
public:
    VertexArray(GLuint max_instances);
    ~VertexArray();

    void bind() const { glBindVertexArray(m_id); }
    void unbind() const { glBindVertexArray(0); }

    void push_vertex(const Vertex vertex);
    void push_index(const GLuint index);
    void push_instance(const InstanceData& instance, GLuint instance_count);

    void set_vertex_data(const std::vector<Vertex>& vertices);
    void set_index_data(const std::vector<GLuint>& indices);

    void send_data();

    GLuint index_count() const { return m_indices.size(); }
    GLuint vertex_count() const { return m_vertices.size(); }
    GLuint get_id() const { return m_id; }
private:
    GLuint m_max_instances;

    GLuint m_id;
    GLuint m_vbo_geometry;
    GLuint m_vbo_instances;
    GLuint m_ebo;

    std::vector<Vertex> m_vertices = {};
    std::vector<GLuint> m_indices = {};

};

}
