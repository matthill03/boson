#include "boson/vertex_array.h"

namespace boson {

VertexArray::VertexArray(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices) {
    glGenVertexArrays(1, &m_id);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    bind();

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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
