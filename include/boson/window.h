#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>

namespace boson {
typedef struct WindowConfig {
    int width;
    int height;
    std::string title;
    glm::vec3 colour;
} WindowConfig_t;

class Window {
public:
    Window(const WindowConfig_t& config);
    ~Window();

    GLFWwindow* get_handle() const { return m_handle; }
    int get_width() const { return m_width; }
    int get_height() const { return m_height; }
    std::string get_title() const { return m_title; }
    glm::vec3 get_colour() const { return m_colour; }

private:
    GLFWwindow* m_handle;
    int m_width;
    int m_height;
    std::string m_title;
    glm::vec3 m_colour;


};
}
