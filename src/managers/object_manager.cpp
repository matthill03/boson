#include "boson/managers/object_manager.h"

namespace boson {

ObjectManager::ObjectManager() {
    m_transform_data.reserve(m_max_buffer_size);
    create_transform_buffer();
}

ObjectManager::~ObjectManager() {
}

void ObjectManager::add_transform(const glm::mat4& value) {
    if (m_transform_data.size() >= m_max_buffer_size) {
        std::cout << "Cannot add transform, toooooooo many!!!!\n";
        return;
    }
    m_transform_data.emplace_back(value);

    glBindBuffer(GL_ARRAY_BUFFER, m_transform_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, (m_transform_data.size() - 1) * sizeof(glm::mat4), sizeof(glm::mat4), &value[0][0]);

}

void ObjectManager::create_transform_buffer() {
    glGenBuffers(1, &m_transform_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_transform_buffer);

    glBufferData(GL_ARRAY_BUFFER, m_max_buffer_size * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);
}

}
