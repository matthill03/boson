#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <unordered_map>
#include <vector>

#include "boson/mesh.h"
#include "boson/shader.h"
#include "boson/texture.h"

namespace boson {

class Renderer {
public:
    Renderer(const Shader& shader);
    ~Renderer();

    void draw(const Mesh& mesh);

private:
    std::unique_ptr<Shader> m_shader = nullptr;

    void render_instanced(const Mesh& mesh);

};

}
