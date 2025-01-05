#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

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
    void set_mat4(const std::string& name, const glm::mat4& mat) const { glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]); };
    void set_vec3(const std::string& name, const glm::vec3& vec) const { glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &vec[0]); };
    void set_float(const std::string& name, float value) const { glUniform1f(glGetUniformLocation(m_id, name.c_str()), value); };

private:
    GLuint m_id;

    void load_shader_file(const std::string& file_path, std::string& code_location);
    std::string shader_type_as_string(ShaderType type);
    void check_compile_errors(GLuint shader, ShaderType type);
};

}
