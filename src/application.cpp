#include "boson/application.h"

namespace boson {
Application::Application(const WindowConfig_t& window_config) {
    m_window = std::make_unique<Window>(window_config);
    m_proj_matrix = glm::perspective(glm::radians(45.0f), (float)window_config.width / (float)window_config.height, 0.1f, 100.0f);
    m_view_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
}

Application::~Application() {
}

void Application::add_obj(const ObjectInfo& obj_info) {
    switch (obj_info.type) {
        case ObjectType::CUBE: {
            std::shared_ptr<Mesh> mesh = m_mesh_manager->get_mesh("cube");

            if (mesh == nullptr) {
                // Item does not exists
                std::string new_mesh = m_mesh_manager->load_cube_mesh();;

                m_obj_data.insert({new_mesh, { Object(obj_info) }});
                break;
            }

            m_obj_data.at("cube").push_back(Object(obj_info));
            break;
        }
        /*case ObjectType::MODEL: {*/
        /*    auto item = m_mesh_data.find(static_cast<GLuint>(obj_info.type));*/
        /**/
        /*    if (item == m_mesh_data.end()) {*/
        /*        // Item does not exists*/
        /*        std::unique_ptr<Mesh> new_mesh = std::make_unique<Mesh>("name", square_vertices, square_indices, m_next_mesh_id);*/
        /*        m_next_mesh_id++;*/
        /**/
        /*        GLuint new_id = new_mesh->get_id();*/
        /**/
        /*        m_mesh_data.insert({new_id, std::move(new_mesh)});*/
        /*        m_obj_data.insert({new_id, { Object(obj_info) }});*/
        /*        break;*/
        /*    }*/
        /**/
        /*    GLuint map_index = item->second.get()->get_id();*/
        /*    m_obj_data.at(map_index).push_back(Object(obj_info));*/
        /*    break;*/
        /*}*/
        default: exit(EXIT_FAILURE);
    }
}

void Application::run() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    Shader shader = Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    Renderer renderer(shader);
    Material material = {
        {0.2f, 0.2f, 0.2},
        {0.6f, 0.6f, 0.6f},
        {0.8f, 0.8f, 0.8f},
        32.0f

    };

    Material material_two = {
        {0.1f, 0.2f, 0.1},
        {0.6f, 0.9f, 0.6f},
        {0.2f, 0.7f, 0.2f},
        128.0f

    };

    add_obj({
        ObjectType::CUBE,
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f},
        {45.0f, 45.0f, 0.0f},
        material,
    });

    add_obj({
        ObjectType::CUBE,
        {-1.5f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f},
        {0.0f, -2.0f, 50.0f},
        material_two,
    });

    add_obj({
        ObjectType::CUBE,
        {1.5f, 2.0f, 0.0f},
        {1.0f, 1.0f, 1.0f},
        {60.0f, -15.0f, 0.0f},
        material,
    });

    add_obj({
        ObjectType::CUBE,
        {1.0f, -1.0f, -4.0f},
        {1.0f, 1.0f, 1.0f},
        {0.0f, 45.0f, 20.0f},
        material,
    });

    /*renderer.add_obj(square_two);*/

    shader.use();
    shader.set_mat4("projection", m_proj_matrix);
    shader.set_mat4("view", m_view_matrix);

    shader.set_vec3("light_pos", {0.0f, 0.0f, 10.0f});
    shader.set_vec3("view_pos", {10.0f, 10.0f, 10.0f});

    while (!glfwWindowShouldClose(m_window->get_handle()))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        for (const auto& obj_set : m_obj_data) {
            renderer.draw(*m_mesh_manager->get_mesh(obj_set.first), obj_set.second);
        }

        glfwSwapBuffers(m_window->get_handle());
        glfwPollEvents();
    }
}
}
