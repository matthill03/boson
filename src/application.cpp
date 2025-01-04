#include "boson/application.h"

namespace boson {
Application::Application(const WindowConfig_t& window_config) {
    m_window = std::make_unique<Window>(window_config);
}

Application::~Application() {
}

void Application::run() {
    Shader shader = Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    Renderer square_renderer(shader);
    Object square({
        ObjectType::SQUARE,
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f}
    });

    /*Object square_two({*/
    /*    ObjectType::SQUARE,*/
    /*    {-0.5f, 1.0f, 0.0f},*/
    /*    {1.0f, 1.0f, 1.0f},*/
    /*    {1.0f, 1.0f, 1.0f}*/
    /*});*/

    square_renderer.add_obj(square);
    //square_renderer.add_obj(square_two);

    while (!glfwWindowShouldClose(m_window->get_handle()))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        square_renderer.draw();

        glfwSwapBuffers(m_window->get_handle());
        glfwPollEvents();
    }
}
}
