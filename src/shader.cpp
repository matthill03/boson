#include "boson/shader.h"

namespace boson {

Shader::Shader(const std::string& vertex_file_path, const std::string& fragment_file_path) {

    std::string vertex_source_content;
    load_shader_file(vertex_file_path, vertex_source_content);

    std::string fragment_source_content;
    load_shader_file(fragment_file_path, fragment_source_content);


    const char* vertex_code = vertex_source_content.c_str();
    const char* fragment_code = fragment_source_content.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_code, NULL);
    glCompileShader(vertexShader);

    // check for shader compile errors
    check_compile_errors(vertexShader, ShaderType::VERTEX);

    // fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_code, NULL);
    glCompileShader(fragmentShader);

    // check for shader compile errors
    check_compile_errors(fragmentShader, ShaderType::FRAGMENT);

    // link shaders
    m_id = glCreateProgram();
    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);
    glLinkProgram(m_id);
    // check for linking errors
    check_compile_errors(m_id, ShaderType::PROGRAM);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::load_shader_file(const std::string& file_path, std::string& code_location) {
    std::ifstream file(file_path);

    std::ostringstream stream;

    stream << file.rdbuf();

    file.close();

    code_location = stream.str();
}

std::string Shader::shader_type_as_string(ShaderType type) {
    switch (type) {
        case ShaderType::PROGRAM: return "PROGRAM";
        case ShaderType::FRAGMENT: return "FRAGMENT";
        case ShaderType::VERTEX: return "VERTEX";
        default: return "INVALID TYPE";
    }
}

void Shader::check_compile_errors(GLuint shader, ShaderType type) {
    int success;
    char infoLog[1024];
    switch (type) {
        case ShaderType::PROGRAM: {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << shader_type_as_string(type) << "\n" << infoLog << "\n -- --------------------------------------------------- -- \n";
            }

        }
        default: {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << shader_type_as_string(type) << "\n" << infoLog << "\n -- --------------------------------------------------- -- \n";
            }
        }


    }
}

Shader::~Shader() {
    glDeleteProgram(m_id);
}

}
