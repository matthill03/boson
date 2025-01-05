#include "boson/renderer.h"

namespace boson {

Renderer::Renderer(const Shader& shader) : m_shader(std::make_unique<Shader>(shader)) {

}

void Renderer::draw(const Mesh& mesh, const std::vector<Object>& obj_list) {

    mesh.bind_data();

    for (const auto& obj : obj_list) {
        m_shader->set_mat4("model", obj.get_model());
        m_shader->set_vec3("material.ambient", obj.get_material().ambient);
        m_shader->set_vec3("material.diffuse", obj.get_material().diffuse);
        m_shader->set_vec3("material.specular", obj.get_material().specular);
        m_shader->set_float("material.shininess", obj.get_material().shininess);

       glDrawElements(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_INT, 0);
    }

}

Renderer::~Renderer() {

}

}
