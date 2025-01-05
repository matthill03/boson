#pragma once
#include <GL/glew.h>

#include <memory>

#include <boson/vertex_array.h>

namespace boson {

class Mesh {
public:
    Mesh(const std::string& name, const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, GLuint next_mesh_id);
    ~Mesh();

    void bind_data() const { m_data->bind(); }

    GLuint get_id() const { return m_id; }
    GLuint get_index_count() const { return m_data->index_count(); }
    std::string get_name() const { return m_name; }

private:
    GLuint m_id;
    std::string m_name;
    std::unique_ptr<VertexArray> m_data = nullptr;

};

}
