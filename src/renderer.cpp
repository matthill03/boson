#include "boson/renderer.h"

namespace boson {

Renderer::Renderer(const Shader& shader) : m_shader(std::make_unique<Shader>(shader)) {

}

void Renderer::render_instanced(const Mesh& mesh) {
    //std::cout << "Rendering Mesh: " << mesh.get_name() << ", Num Instances: " << mesh.get_instance_count() << "\n";

    std::vector<Texture> textures = mesh.get_textures();
    //std::cout << "texture number: " << textures.size() << "\n";

    for (int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        textures[i].bind();

        m_shader->set_int("textures[" + std::to_string(i) + "]", i);

    }

    m_shader->set_float("material.shininess", mesh.get_shininess());

    glDrawElementsInstanced(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_INT, 0, mesh.get_instance_count());

    glActiveTexture(GL_TEXTURE0);

}

void Renderer::draw(const Mesh& mesh, const std::vector<Object>& obj_list) {

    mesh.bind_data();

    render_instanced(mesh);
}

Renderer::~Renderer() {

}

}
