#include "boson/renderer.h"

namespace boson {

Renderer::Renderer(const Shader& shader) : m_shader(std::make_unique<Shader>(shader)) {

}

void Renderer::render_instanced(const Mesh& mesh) {
    //std::cout << "Rendering Mesh: " << mesh.get_name() << ", Num Instances: " << mesh.get_instance_count() << "\n";

    std::vector<Texture> textures = mesh.get_textures();
    std::vector<GPUMaterial> materials = mesh.get_materials();

    //std::cout << "texture number: " << textures.size() << "\n";

    for (int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        textures[i].bind();

        m_shader->set_int("textures[" + std::to_string(i) + "]", i);

    }

    for (int i = 0; i < materials.size(); i++) {
        m_shader->set_vec3("materials[" + std::to_string(i) + "].ambient", materials[i].ambient);
        m_shader->set_vec3("materials[" + std::to_string(i) + "].diffuse", materials[i].diffuse);
        m_shader->set_vec3("materials[" + std::to_string(i) + "].specular", materials[i].specular);
        m_shader->set_int("materials[" + std::to_string(i) + "].diffuse_map", materials[i].diffuse_map);
        m_shader->set_int("materials[" + std::to_string(i) + "].specular_map", materials[i].specular_map);
        m_shader->set_float("materials[" + std::to_string(i) + "].shininess", materials[i].shininess);
    }


    //m_shader->set_float("material.shininess", mesh.get_shininess());

    glDrawElementsInstanced(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_INT, 0, mesh.get_instance_count());

    glActiveTexture(GL_TEXTURE0);

}

void Renderer::draw(const Mesh& mesh) {

    mesh.bind_data();

    render_instanced(mesh);
}

Renderer::~Renderer() {

}

}
