#include "boson/mesh.h"

namespace boson {

Mesh::Mesh(const std::string& name, GLuint next_mesh_id) : m_name(name), m_id(next_mesh_id) {
    m_data = std::make_unique<VertexArray>();
}

Mesh::Mesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLuint next_mesh_id) : m_name(name), m_id(next_mesh_id) {
    m_data = std::make_unique<VertexArray>();
    m_data->set_vertex_data(vertices);
    m_data->set_index_data(indices);
    m_data->send_data();
}

void Mesh::push_vertex(const Vertex vertex) {
    m_data->push_vertex(vertex);
}

void Mesh::push_index(const GLuint index) {
    m_data->push_index(index);
}

void Mesh::send_data() {
    m_data->send_data();
}
void Mesh::add_texture(const std::string& file_path, TextureType type) {
    m_textures.emplace_back(file_path, type);
}


Mesh::~Mesh() {

}

}
