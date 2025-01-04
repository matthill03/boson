#include "boson/application.h"

namespace boson {
Application::Application(const WindowConfig_t& window_config) {
    m_window = std::make_unique<Window>(window_config);
}

Application::~Application() {
}

void Application::run() {
    std::vector<GLfloat> vertices = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };

    std::vector<GLuint> indices = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    Shader shader = Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    VertexArray square(vertices, indices);

    while (!glfwWindowShouldClose(m_window->get_handle()))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        square.bind();

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(m_window->get_handle());
        glfwPollEvents();
    }
}
}
