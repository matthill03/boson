#pragma once
#include <glad/gl.h>
#include <stb_image.h>

#include <vector>
#include <string>

#include "boson/shader.h"
#include "boson/renderer.h"

#define SKYBOX_VERTEX_SHADER "../lib/boson/resources/shaders/skybox_vertex.glsl"
#define SKYBOX_FRAGMENT_SHADER "../lib/boson/resources/shaders/skybox_fragment.glsl"

namespace boson {

class Skybox {
public:
    Skybox(const std::vector<std::string>& map_textures);
    ~Skybox();

    void draw(const glm::mat4& view, const glm::mat4& projection) const;

private:
    GLuint m_id;
    GLuint m_vao;
    GLuint m_vbo;

    std::shared_ptr<Shader> m_shader = std::make_shared<Shader>(SKYBOX_VERTEX_SHADER, SKYBOX_FRAGMENT_SHADER);

    void bind_texture() const { glBindTexture(GL_TEXTURE_CUBE_MAP, m_id); }
    void unbind_texture() const { glBindTexture(GL_TEXTURE_CUBE_MAP, 0); }
    void bind_vao() const { glBindVertexArray(m_vao); }
    void unbind_vao() const { glBindVertexArray(0); }

    void create_vao();

    std::vector<GLfloat> m_vertices = {
        // positions
        -1000.0f,  1000.0f, -1000.0f,
        -1000.0f, -1000.0f, -1000.0f,
         1000.0f, -1000.0f, -1000.0f,
         1000.0f, -1000.0f, -1000.0f,
         1000.0f,  1000.0f, -1000.0f,
        -1000.0f,  1000.0f, -1000.0f,

        -1000.0f, -1000.0f,  1000.0f,
        -1000.0f, -1000.0f, -1000.0f,
        -1000.0f,  1000.0f, -1000.0f,
        -1000.0f,  1000.0f, -1000.0f,
        -1000.0f,  1000.0f,  1000.0f,
        -1000.0f, -1000.0f,  1000.0f,

         1000.0f, -1000.0f, -1000.0f,
         1000.0f, -1000.0f,  1000.0f,
         1000.0f,  1000.0f,  1000.0f,
         1000.0f,  1000.0f,  1000.0f,
         1000.0f,  1000.0f, -1000.0f,
         1000.0f, -1000.0f, -1000.0f,

        -1000.0f, -1000.0f,  1000.0f,
        -1000.0f,  1000.0f,  1000.0f,
         1000.0f,  1000.0f,  1000.0f,
         1000.0f,  1000.0f,  1000.0f,
         1000.0f, -1000.0f,  1000.0f,
        -1000.0f, -1000.0f,  1000.0f,

        -1000.0f,  1000.0f, -1000.0f,
         1000.0f,  1000.0f, -1000.0f,
         1000.0f,  1000.0f,  1000.0f,
         1000.0f,  1000.0f,  1000.0f,
        -1000.0f,  1000.0f,  1000.0f,
        -1000.0f,  1000.0f, -1000.0f,

        -1000.0f, -1000.0f, -1000.0f,
        -1000.0f, -1000.0f,  1000.0f,
         1000.0f, -1000.0f, -1000.0f,
         1000.0f, -1000.0f, -1000.0f,
        -1000.0f, -1000.0f,  1000.0f,
         1000.0f, -1000.0f,  1000.0f
    };

};

}
