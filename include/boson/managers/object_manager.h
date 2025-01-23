#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>

namespace boson {

class ObjectManager {
public:
    ObjectManager();
    ~ObjectManager();

    void add_transform(const glm::mat4& value);

private:
    GLuint m_transform_buffer;
    GLuint m_max_buffer_size = 1000;

    std::vector<glm::mat4> m_transform_data = {};

    void create_transform_buffer();
};

}
