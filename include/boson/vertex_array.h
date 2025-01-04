#pragma once
#include <GL/glew.h>
#include <vector>

namespace boson {

class VertexArray {
public:
    VertexArray(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
    ~VertexArray();

    void bind() const { glBindVertexArray(m_id); }
    void unbind() const { glBindVertexArray(0); }

    GLuint index_count() const { return m_index_count; }
    GLuint get_id() const { return m_id; }
private:
    GLuint m_id;
    GLuint m_vbo;
    GLuint m_ebo;

    GLuint m_index_count;

};

}
