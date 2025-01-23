#pragma once
#include <glad/gl.h>
#include <stb_image.h>

#include <string>

namespace boson {

enum class TextureType {
    DIFFUSE,
    SPECULAR,
};

class Texture {
public:
    Texture(const std::string& file_path, TextureType type);
    ~Texture();

    void bind() const { glBindTexture(GL_TEXTURE_2D, m_id); }
    void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

    GLuint get_id() const { return m_id; }
    TextureType get_type() const { return m_type; }

private:
    GLuint m_id;
    TextureType m_type;
    std::string m_file_path;

};

}
