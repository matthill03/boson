#include "boson/renderer.h"
#include "glm/ext/matrix_transform.hpp"
#include <glm/gtx/string_cast.hpp>

namespace boson {

Renderer::Renderer(const Shader& shader) : m_shader(std::make_unique<Shader>(shader)) {

}

void Renderer::render_data(const Object& obj, const Mesh& mesh) {

    /*glm::mat4 new_matrix = glm::translate(obj.get_model(), glm::vec3(mesh.get_base_tranform()[3]));*/
    /*m_shader->set_mat4("model", new_matrix);*/

    GLuint diffuse_count = 0;
    GLuint specular_count = 0;
    std::vector<Texture> textures;
    if (mesh.get_textures().size() > 0) {
        textures = mesh.get_textures();
    } else {
        textures = obj.get_textures();
    }

    for (int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        textures[i].bind();

        if (textures[i].get_type() == TextureType::DIFFUSE) {
            m_shader->set_int("material.diffuse", i);
            diffuse_count++;
        } else if (textures[i].get_type() == TextureType::SPECULAR) {
            m_shader->set_int("material.specular", i);
            specular_count++;
        }
    }

    m_shader->set_float("material.shininess", obj.get_shininess());

    glDrawElements(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_INT, 0);

    glActiveTexture(GL_TEXTURE0);
}

void Renderer::render_instanced(const Mesh& mesh) {

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
