#include "boson/renderer.h"

#include "glm/gtx/string_cast.hpp"
#include <memory>

namespace boson {

Renderer::Renderer(const Shader& shader) : m_shader(std::make_unique<Shader>(shader)) {

}

void Renderer::add_obj(const Object& obj) {
    //m_object_matrices.push_back(obj.get_model());
    switch (obj.get_type()) {
        case ObjectType::SQUARE: {
            auto item = m_vertex_arrays.find(ObjectType::SQUARE);

            if (item == m_vertex_arrays.end()) {
                // Item does not exists
                std::unique_ptr<VertexArray> new_vert_array = std::make_unique<VertexArray>(square_vertices, square_indices);
                GLuint new_id = new_vert_array->get_id();

                m_vertex_arrays.insert({ObjectType::SQUARE, std::move(new_vert_array)});
                m_obj_data.insert({new_id, { obj.get_model() }});
                //m_data.at(new_vert_array->get_id()).push_back(obj.get_model());
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
    for (const auto& vertex_array : m_vertex_arrays) {
        vertex_array.second->bind();

        for (const auto& obj : m_obj_data.at(vertex_array.second->get_id())) {
            std::cout << glm::to_string(obj) << "\n";
            m_shader->set_mat4("transform", obj);

           glDrawElements(GL_TRIANGLES, vertex_array.second->index_count(), GL_UNSIGNED_INT, 0);
        }

    }
}

Renderer::~Renderer() {

}

}
