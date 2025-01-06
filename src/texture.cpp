#include "boson/texture.h"
#include <iostream>

namespace boson {

Texture::Texture(const std::string& file_path, TextureType type) : m_file_path(file_path), m_type(type){
    glGenTextures(1, &m_id);
    bind();

    GLint width, height, nr_channels;
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(file_path.c_str(), &width, &height, &nr_channels, STBI_rgb_alpha);
    std::cout << width << ", " << height << ", " << nr_channels << "\n";
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        exit(EXIT_FAILURE);
    }
    stbi_image_free(data);
    unbind();
}

Texture::~Texture() {

}

}
