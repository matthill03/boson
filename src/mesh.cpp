#include "boson/mesh.h"

namespace boson {

Mesh::Mesh(const std::string& name, const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, GLuint next_mesh_id) : m_name(name), m_id(next_mesh_id) {
    m_data = std::make_unique<VertexArray>(vertices, indices);
}

Mesh::~Mesh() {

}

}
