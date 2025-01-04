#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

namespace neptune {
typedef struct WindowConfig {
    int width;
    int height;
    std::string title;

} WindowConfig_t;

class Window {
public:
    Window(const WindowConfig_t& config);
    ~Window();

    GLFWwindow* get_handle() const { return m_handle; }

private:
    GLFWwindow* m_handle;
    int m_width;
    int m_height;
    std::string m_title;


};
}
