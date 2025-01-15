#include "boson/object.h"

namespace boson {

Object::Object(const ObjectInfoMat& info) : m_material(info.material), m_shininess(info.material.shininess) {
    m_model_matrix = glm::scale(m_model_matrix, {info.size.x, info.size.y, info.size.z});

    m_model_matrix = glm::rotate(m_model_matrix, glm::radians(info.rotation.x), {1.0f, 0.0f, 0.0f});
    m_model_matrix = glm::rotate(m_model_matrix, glm::radians(info.rotation.y), {0.0f, 1.0f, 0.0f});
    m_model_matrix = glm::rotate(m_model_matrix, glm::radians(info.rotation.z), {0.0f, 0.0f, 1.0f});

    m_model_matrix = glm::translate(m_model_matrix, {-info.position.x / info.size.x, info.position.y / info.size.y, info.position.z / -info.size.z});

}

Object::Object(const ObjectInfoTex& info) : m_textures(info.textures), m_shininess(info.shininess) {
    m_model_matrix = glm::scale(m_model_matrix, {info.size.x, info.size.y, info.size.z});

    m_model_matrix = glm::rotate(m_model_matrix, glm::radians(info.rotation.x), {1.0f, 0.0f, 0.0f});
    m_model_matrix = glm::rotate(m_model_matrix, glm::radians(info.rotation.y), {0.0f, 1.0f, 0.0f});
    m_model_matrix = glm::rotate(m_model_matrix, glm::radians(info.rotation.z), {0.0f, 0.0f, 1.0f});

    m_model_matrix = glm::translate(m_model_matrix, {info.position.x / info.size.x, info.position.y / info.size.y, info.position.z / info.size.z});
}

Object::~Object() {

}

void Object::add_texture(const std::string& file_path, TextureType type) {
    Texture new_texture = Texture(file_path, type);
    m_textures.push_back(new_texture);
}

void Object::add_texture(const Texture& texture) {
    m_textures.push_back(texture);
}

}
