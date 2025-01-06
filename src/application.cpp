#include "boson/application.h"

namespace boson {
Application::Application(const WindowConfig_t& window_config) {
    m_window = std::make_unique<Window>(window_config);
    m_proj_matrix = glm::perspective(glm::radians(45.0f), (float)window_config.width / (float)window_config.height, 0.1f, 100.0f);
    m_view_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, -10.0f));
}

Application::~Application() {
}

void Application::add_model(const ModelInfo& info) {
    std::shared_ptr<Mesh> mesh = m_mesh_manager->get_mesh(info.file_path);

    if (mesh == nullptr) {
        std::shared_ptr<Mesh> new_mesh = m_mesh_manager->load_model_mesh(info.file_path);
        Object new_obj = Object({info.position, info.size, info.rotation, info.textures.value_or(new_mesh->get_textures()), info.shininess.value_or(new_mesh->get_shininess())});
        new_mesh->push_instance({new_obj.get_model(), 0, 0});

        return;
    }
    Object new_obj = Object({info.position, info.size, info.rotation, info.textures.value_or(mesh->get_textures()), info.shininess.value_or(mesh->get_shininess())});
    mesh->push_instance({new_obj.get_model(), 0, 0});

}

void Application::add_cube(const CubeInfo& info) {
    std::shared_ptr<Mesh> mesh = m_mesh_manager->get_mesh("cube");

    if (mesh == nullptr) {
        // Item does not exists
        std::string new_mesh_name = m_mesh_manager->load_cube_mesh();;
        std::shared_ptr<Mesh> mesh = m_mesh_manager->get_mesh(new_mesh_name);
        Object new_obj = Object({info.position, info.size, info.rotation, info.material});
        mesh->push_instance({new_obj.get_model(), 0, 0});

        //m_obj_data.insert({new_mesh, { Object({info.position, info.size, info.rotation, info.material}) }});
        return;
    }

    m_obj_data.at("cube").push_back(Object({info.position, info.size, info.rotation, info.material}));
}

void Application::add_plane(const PlaneInfo& info) {
    std::shared_ptr<Mesh> mesh = m_mesh_manager->get_mesh("plane");

    if (mesh == nullptr) {
        // Item does not exists
        std::string new_mesh = m_mesh_manager->load_plane_mesh();;

        m_obj_data.insert({new_mesh, { Object({info.position, glm::vec3(info.size.x, 1.0f, info.size.y), info.rotation, info.material}) }});
        return;
    }

    m_obj_data.at("plane").push_back(Object({info.position, glm::vec3(info.size.x, 1.0f, info.size.y), info.rotation, info.material}));
}

void Application::add_sphere(const SphereInfo& info) {
    std::string sphere_name = "sphere_" + std::to_string(info.sector_count) + "_" + std::to_string(info.stack_count) + "_" + std::to_string(static_cast<GLint>(info.radius));

    std::shared_ptr<Mesh> mesh = m_mesh_manager->get_mesh(sphere_name);

    if (mesh == nullptr) {
        // Item does not exists
        std::string new_mesh = m_mesh_manager->load_sphere_mesh(info.sector_count, info.stack_count, info.radius, sphere_name);

        m_obj_data.insert({new_mesh, { Object({info.position, glm::vec3(1.0f), info.rotation, info.material}) }});
        return;
    }

    m_obj_data.at(sphere_name).push_back(Object({info.position, glm::vec3(1.0f), info.rotation, info.material}));

}

void Application::add_cylinder(const CylinderInfo& info) {
    std::string cylinder_name = "cylinder_" + std::to_string(info.sector_count) + "_" + std::to_string(static_cast<GLint>(info.radius)) + "_" + std::to_string(static_cast<GLint>(info.height));

    std::shared_ptr<Mesh> mesh = m_mesh_manager->get_mesh(cylinder_name);

    if (mesh == nullptr) {
        // Item does not exists
        std::string new_mesh = m_mesh_manager->load_cylinder_mesh(info.sector_count, info.radius, info.height, cylinder_name);

        m_obj_data.insert({new_mesh, { Object({info.position, glm::vec3(1.0f), info.rotation, info.material}) }});
        return;
    }

    m_obj_data.at(cylinder_name).push_back(Object({info.position, glm::vec3(1.0f), info.rotation, info.material}));
}

void Application::run() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    Shader shader = Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    Renderer renderer(shader);

    Texture diffuse("../resources/diffuse_box.png", TextureType::DIFFUSE);
    Texture specular("../resources/specular_box.png", TextureType::SPECULAR);
    std::vector<Texture> textures = {diffuse, specular};

    add_model({
        .position = {1.0f, 0.0f, 0.0f},
        .size = {1.0f, 1.0f, 1.0f},
        .rotation = {0.0f, 45.0f, 0.0f},
        .textures = textures,
        .shininess = 32.0f,
        .file_path = "../resources/cube.obj",
    });

    add_model({
        .position = {6.0f, 0.0f, 0.0f},
        .size = {1.0f, 1.0f, 1.0f},
        .rotation = {0.0f, 45.0f, 0.0f},
        .textures = textures,
        .shininess = 32.0f,
        .file_path = "../resources/cube.obj",
    });

    add_model({
        .position = {-4.0f, 0.0f, 0.0f},
        .size = {1.0f, 1.0f, 1.0f},
        .rotation = {0.0f, 45.0f, 0.0f},
        .textures = textures,
        .shininess = 32.0f,
        .file_path = "../resources/cube.obj",
    });

    /*add_model({*/
    /*    .position = {1.0f, 2.0f, -6.0f},*/
    /*    .size = {0.2f, 0.2f, 0.2f},*/
    /*    .rotation = {0.0f, 0.0f, 0.0f},*/
    /*    .shininess = 32.0f,*/
    /*    .file_path = "../resources/latern/Lantern.gltf",*/
    /*});*/

    /*add_plane({*/
    /*    .position = {1.0f, -10.0f, 0.0f},*/
    /*    .size = {100.0f, 200.0f},*/
    /*    .rotation = {0.0f, 0.0f, 0.0f},*/
    /*    .material = material,*/
    /*});*/

    shader.use();
    shader.set_mat4("projection", m_proj_matrix);
    shader.set_mat4("view", m_view_matrix);

    shader.set_vec3("light_pos", {0.0f, 0.0f, 10.0f});
    shader.set_vec3("view_pos", {10.0f, 10.0f, 10.0f});

    while (!glfwWindowShouldClose(m_window->get_handle()))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        /*for (const auto& obj_set : m_obj_data) {*/
        /*    renderer.draw(*m_mesh_manager->get_mesh(obj_set.first), obj_set.second);*/
        /*}*/

        for (const auto& mesh : m_mesh_manager->get_meshes()) {
            renderer.draw(*mesh.second, {});
        }


        glfwSwapBuffers(m_window->get_handle());
        glfwPollEvents();
    }
}
}
