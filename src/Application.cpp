#include "boson/Application.h"

namespace boson {
Application::Application(const WindowConfig_t& window_config) {
    m_window = std::make_unique<Window>(window_config);
}

Application::~Application() {
}

void Application::run() {
    while (!glfwWindowShouldClose(m_window->get_handle()))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(m_window->get_handle());
        glfwPollEvents();
    }
}
}
