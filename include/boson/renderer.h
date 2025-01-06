#pragma once
#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <unordered_map>
#include <vector>

#include "boson/mesh.h"
#include "boson/object.h"
#include "boson/shader.h"
#include "boson/texture.h"

namespace boson {

class Renderer {
public:
    Renderer(const Shader& shader);
    ~Renderer();

    void draw(const Mesh& mesh, const std::vector<Object>& obj_list);

private:
    std::unique_ptr<Shader> m_shader = nullptr;

    void render_data(const Object& obj, const Mesh& mesh);

};

}
