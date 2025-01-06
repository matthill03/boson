#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <memory>

#include <boson/vertex_array.h>
#include <boson/texture.h>
#include "boson/object.h"

namespace boson {

class Mesh {
public:
    Mesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLuint next_mesh_id);
    Mesh(const std::string& name, GLuint next_mesh_id);
    ~Mesh();

    void bind_data() const { m_data->bind(); }

    void push_vertex(const Vertex vertex);
    void push_index(const GLuint index);

    void send_data();

    void set_shininess(GLfloat value) { m_shininess = value; };
    void set_base_tranform(glm::mat4 transform) { m_base_transform = transform; }

    GLuint get_id() const { return m_id; }
    GLuint get_index_count() const { return m_data->index_count(); }
    GLuint get_vertex_count() const { return m_data->vertex_count(); }
    std::string get_name() const { return m_name; }

    std::vector<Texture> get_textures() const { return m_textures; }
    GLfloat get_shininess() const { return m_shininess; }
    glm::mat4 get_base_tranform() const { return m_base_transform; }

    std::vector<std::shared_ptr<Mesh>> get_children() const { return m_child_data; }

    bool has_children() const { return m_child_data.size() > 0; };

    void add_texture(const std::string& file_path, TextureType type);
    void add_child(std::shared_ptr<Mesh> child) { m_child_data.push_back(child); };

private:
    GLuint m_id;
    std::string m_name;
    std::unique_ptr<VertexArray> m_data = nullptr;
    std::vector<std::shared_ptr<Mesh>> m_child_data = {};

    glm::mat4 m_base_transform;

    std::vector<Texture> m_textures = {};
    GLfloat m_shininess = 1.0f;
};

}
