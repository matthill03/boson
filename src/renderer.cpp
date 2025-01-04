#include "boson/renderer.h"

namespace boson {

Renderer::Renderer(const Shader& shader) : m_shader(std::make_unique<Shader>(shader)) {

}

void Renderer::add_obj(const Object& obj) {
    switch (obj.get_type()) {
        case ObjectType::CUBE: {
            auto item = m_vertex_arrays.find(ObjectType::CUBE);

            if (item == m_vertex_arrays.end()) {
                // Item does not exists
                std::unique_ptr<VertexArray> new_vert_array = std::make_unique<VertexArray>(square_vertices, square_indices);
                GLuint new_id = new_vert_array->get_id();

                m_vertex_arrays.insert({ObjectType::CUBE, std::move(new_vert_array)});
                m_obj_data.insert({new_id, { obj.get_model() }});
                break;
            }

            GLuint map_index = item->second.get()->get_id();
            m_obj_data.at(map_index).push_back(obj.get_model());
            break;
        }
        default: exit(EXIT_FAILURE);

    }
}

void Renderer::draw() {
    m_shader->set_mat4("projection", m_proj_matrix);
    m_shader->set_mat4("view", m_view_matrix);

    m_shader->set_vec3("light_pos", {0.0f, 0.0f, 10.0f});
    m_shader->set_vec3("view_pos", {0.0f, 0.0f, 10.0f});

    for (const auto& vertex_array : m_vertex_arrays) {
        vertex_array.second->bind();

        for (const auto& obj : m_obj_data.at(vertex_array.second->get_id())) {
            m_shader->set_mat4("model", obj);
            m_shader->set_vec3("material.colour", {0.7f, 0.8f, 0.9f});

           glDrawElements(GL_TRIANGLES, vertex_array.second->index_count(), GL_UNSIGNED_INT, 0);
        }

    }
}

Renderer::~Renderer() {

}

}
