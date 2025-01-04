#pragma once
#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace boson {

enum class ShaderType {
    VERTEX,
    FRAGMENT,
    PROGRAM
};

class Shader {
public:
    Shader(const std::string& vertex_file_path, const std::string& fragment_file_path);
    ~Shader();

    void use() const { glUseProgram(m_id); }

private:
    GLuint m_id;

    void load_shader_file(const std::string& file_path, std::string& code_location);
    std::string shader_type_as_string(ShaderType type);
    void check_compile_errors(GLuint shader, ShaderType type);
};

}
