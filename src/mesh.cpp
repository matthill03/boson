#include "boson/mesh.h"

namespace boson {

Mesh::Mesh(const std::string& name, GLuint next_mesh_id) : m_name(name), m_id(next_mesh_id) {
    m_data = std::make_unique<VertexArray>(m_max_data_size);

    m_instance_transform_data.reserve(m_max_data_size);
}

Mesh::Mesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLuint next_mesh_id) : m_name(name), m_id(next_mesh_id) {
    m_data = std::make_unique<VertexArray>(m_max_data_size);
    m_data->set_vertex_data(vertices);
    m_data->set_index_data(indices);
    m_data->send_data();

    m_instance_transform_data.reserve(m_max_data_size);
}

void Mesh::push_vertex(const Vertex vertex) {
    m_data->push_vertex(vertex);
}

void Mesh::push_index(const GLuint index) {
    m_data->push_index(index);
}

void Mesh::push_instance(const glm::mat4& instance) {
    if (m_instance_transform_data.size() >= m_max_data_size) {
        std::cout << "Woooooah, tooo many lad...\n";
        return;
    }

    m_data->push_instance(instance, m_instance_transform_data.size());
    m_instance_transform_data.emplace_back(instance);
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
