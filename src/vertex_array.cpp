#include "boson/vertex_array.h"

namespace boson {

VertexArray::VertexArray(GLuint max_instances) : m_max_instances(max_instances){
    glGenVertexArrays(1, &m_id);
    glGenBuffers(1, &m_vbo_geometry);
    glGenBuffers(1, &m_vbo_instances);
    glGenBuffers(1, &m_ebo);

    bind();
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_instances);
    glBufferData(GL_ARRAY_BUFFER, m_max_instances * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);

    for (int i = 0; i < 4; i++) {
        glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * i));
        glEnableVertexAttribArray(3 + i);
        glVertexAttribDivisor(3 + i, 1);
    }
    unbind();
}

void VertexArray::push_vertex(const Vertex vertex) {
    m_vertices.push_back(vertex);
}

void VertexArray::push_index(const GLuint index) {
    m_indices.push_back(index);
}

void VertexArray::push_instance(const glm::mat4& instance, GLuint data_size) {
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_instances);
    glBufferSubData(GL_ARRAY_BUFFER, data_size * sizeof(glm::mat4), sizeof(glm::mat4), &instance[0][0]);
    unbind();
}

void VertexArray::set_vertex_data(const std::vector<Vertex>& vertices) {
    m_vertices = vertices;
}

void VertexArray::set_index_data(const std::vector<GLuint>& indices) {
    m_indices = indices;
}

void VertexArray::send_data() {
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    if (m_vertices.empty() || m_indices.empty()) {
        std::cout << "empty\n";
        exit(EXIT_FAILURE);
    }

    bind();

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_geometry);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    unbind();

}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_id);
    glDeleteBuffers(1, &m_vbo_geometry);
    glDeleteBuffers(1, &m_vbo_instances);
    glDeleteBuffers(1, &m_ebo);
}

}
