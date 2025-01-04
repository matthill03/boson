#include "boson/application.h"

namespace boson {
Application::Application(const WindowConfig_t& window_config) {
    m_window = std::make_unique<Window>(window_config);
}

Application::~Application() {
}

void Application::run() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    Shader shader = Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    Renderer renderer(shader);
    Object square({
        ObjectType::CUBE,
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f},
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    });

    /*Object square_two({*/
    /*    ObjectType::CUBE,*/
    /*    {-0.5f, 1.0f, 0.0f},*/
    /*    {1.0f, 1.0f, 1.0f},*/
    /*    {1.0f, 1.0f, 1.0f}*/
    /*});*/

    renderer.add_obj(square);
    /*renderer.add_obj(square_two);*/

    while (!glfwWindowShouldClose(m_window->get_handle()))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        renderer.draw();

        glfwSwapBuffers(m_window->get_handle());
        glfwPollEvents();
    }
}
}
