#include "boson/object.h"

namespace boson {

Object::Object(const ObjectInfo& info) : m_type(info.type) {
    m_model_matrix = glm::scale(m_model_matrix, {info.size.x, info.size.y, info.size.z});

    m_model_matrix = glm::rotate(m_model_matrix, glm::radians(info.rotation.x), {1.0f, 0.0f, 0.0f});
    m_model_matrix = glm::rotate(m_model_matrix, glm::radians(info.rotation.y), {0.0f, 1.0f, 0.0f});
    m_model_matrix = glm::rotate(m_model_matrix, glm::radians(info.rotation.z), {0.0f, 0.0f, 1.0f});

    m_model_matrix = glm::translate(m_model_matrix, {info.position.x / info.size.x, info.position.y / info.size.y, info.position.z / info.size.z});
}

Object::~Object() {

}

}
