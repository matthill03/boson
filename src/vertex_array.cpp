#include "boson/vertex_array.h"

namespace boson {

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_id);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);
}

void VertexArray::push_vertex(const Vertex vertex) {
    m_vertices.push_back(vertex);
}

void VertexArray::push_index(const GLuint index) {
    m_indices.push_back(index);
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
        exit(EXIT_FAILURE);
    }

    bind();

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    unbind();

}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_id);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

}
