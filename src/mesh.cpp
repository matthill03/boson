#include "boson/mesh.h"

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

    process_instance_material(instance);
    GLint material_index = m_materials.size() - 1;

    InstanceData new_instance = {
        .transform = instance.transform,
        .material_index = material_index,
    };

    m_data->push_instance(new_instance, m_instance_data.size());
    m_instance_data.emplace_back(new_instance);

}

void Mesh::push_instance_gpu(glm::mat4 transform, int material_index) {
    if (m_instance_data.size() >= m_max_data_size) {
        std::cout << "Woooooah, tooo many lad...\n";
        return;
    }

    InstanceData new_instance = {
        .transform = transform,
        .material_index = material_index,
    };

    m_data->push_instance(new_instance, m_instance_data.size());
    m_instance_data.emplace_back(new_instance);

}

void Mesh::send_data() {
    m_data->send_data();
}

void Mesh::add_texture(const std::string& file_path, TextureType type) {
    m_textures.emplace_back(file_path, type);
}

void Mesh::add_material(const GPUMaterial& material) {
    m_materials.emplace_back(material);
}

void Mesh::process_instance_material(const InstanceInfo& info) {
    GLint diffuse_map_index = -1;
    GLint specular_map_index = -1;

    for (const auto& texture : info.material.texture_maps) {
        switch (texture.get_type()) {
            case TextureType::DIFFUSE: {
                m_textures.emplace_back(texture);
                diffuse_map_index = m_textures.size() - 1;
                break;
            }
            case TextureType::SPECULAR: {
                m_textures.emplace_back(texture);
                specular_map_index = m_textures.size() - 1;
                break;
            }
            default: exit(EXIT_FAILURE);
        }
    }

    GPUMaterial new_mat = {
        .ambient = info.material.ambient,
        .diffuse = info.material.diffuse,
        .specular = info.material.specular,
        .diffuse_map = diffuse_map_index,
        .specular_map = specular_map_index,
        .shininess = info.material.shininess,
    };

    m_materials.push_back(new_mat);
}

Mesh::~Mesh() {

}

}
