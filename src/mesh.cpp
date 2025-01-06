#include "boson/mesh.h"
#include "boson/texture.h"

namespace boson {

Mesh::Mesh(const std::string& name, GLuint next_mesh_id) : m_name(name), m_id(next_mesh_id) {
    m_data = std::make_unique<VertexArray>(m_max_data_size);

    m_instance_data.reserve(m_max_data_size);
}

Mesh::Mesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLuint next_mesh_id) : m_name(name), m_id(next_mesh_id) {
    m_data = std::make_unique<VertexArray>(m_max_data_size);
    m_data->set_vertex_data(vertices);
    m_data->set_index_data(indices);
    m_data->send_data();

    m_instance_data.reserve(m_max_data_size);
}

void Mesh::push_vertex(const Vertex vertex) {
    m_data->push_vertex(vertex);
}

void Mesh::push_index(const GLuint index) {
    m_data->push_index(index);
}

void Mesh::push_instance(const InstanceInfo& instance) {
    if (m_instance_data.size() >= m_max_data_size) {
        std::cout << "Woooooah, tooo many lad...\n";
        return;
    }

    InstanceData new_instance = {
        .transform = instance.transform,
    };

    for (const auto& texture : instance.textures) {
        switch (texture.get_type()) {
            case TextureType::DIFFUSE: {
                m_textures.emplace_back(texture);
                new_instance.diffuse_map = m_textures.size() - 1;
                break;
            }
            case TextureType::SPECULAR: {
                m_textures.emplace_back(texture);
                new_instance.specular_map = m_textures.size() - 1;
                break;
            }
            default: exit(EXIT_FAILURE);
        }
    }

    m_data->push_instance(new_instance, m_instance_data.size());
    m_instance_data.emplace_back(new_instance);

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
