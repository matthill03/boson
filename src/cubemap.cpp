#include "boson/cubemap.h"
#include "boson/application.h"

namespace boson {

Skybox::Skybox(const std::vector<std::string>& map_textures) {
    glGenTextures(1, &m_id);
    bind_texture();

    GLint width, height, nr_channels;
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    for (int i = 0; i < map_textures.size(); i++) {
        unsigned char *data = stbi_load(map_textures[i].c_str(), &width, &height, &nr_channels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            exit(EXIT_FAILURE);
        }
        stbi_image_free(data);
    }

    create_vao();

    m_shader->use();
    m_shader->set_int("skybox", 0);
}

void Skybox::draw(const glm::mat4& view, const glm::mat4& projection) const {
    glDepthFunc(GL_LEQUAL);
    m_shader->use();


    glm::mat4 view_for_shader = glm::mat4(glm::mat3(view));
    m_shader->set_mat4("view", view_for_shader);
    m_shader->set_mat4("projection", projection);

    glBindVertexArray(m_vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}

void Skybox::create_vao() {
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    bind_vao();
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    unbind_vao();
}

Skybox::~Skybox() {

}
}
