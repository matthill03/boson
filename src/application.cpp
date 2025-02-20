#include "boson/application.h"
#include "boson/mesh.h"
#include <string>

namespace boson {

Application::Application(const WindowConfig_t& window_config) {
    m_window = std::make_unique<Window>(window_config);
    m_proj_matrix = glm::perspective(glm::radians(45.0f), (float)window_config.width / (float)window_config.height, 0.1f, 100.0f);
    m_view_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, -20.0f));
}

Application::~Application() {
}

void Application::set_directional_light(const DirectionalLight& light) {
    m_light_manager->set_directional_light(light);
}

void Application::add_point_light(const PointLight& light) {
    m_light_manager->add_point_light(light);
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

    Texture diffuse_two("../resources/cobblestone.png", TextureType::DIFFUSE);
    Texture specular_two("../resources/cobble_spec.png", TextureType::SPECULAR);
    std::vector<Texture> textures_two = {diffuse_two, specular_two};

    Texture house_diffuse("../resources/cottage/Cottage_Clean_Base_Color.png", TextureType::DIFFUSE);
    std::vector<Texture> house_texture = { house_diffuse };

    Texture road_diffuse("../resources/cobblestone.png", TextureType::DIFFUSE);
    Texture road_specular("../resources/cobble_spec.png", TextureType::SPECULAR);
    std::vector<Texture> road_texture = { road_diffuse, road_specular };

    Material box_material = {
        .texture_maps = textures,
    };

    Material house_material = {
        .texture_maps = house_texture,
    };

    Material road_material = {
        .texture_maps = road_texture,
    };


    //add_sphere({
    //    .position = {},
    //    .sector_count = 32,
    //    .stack_count = 16,
    //    .radius = 1,
    //}, m_mesh_manager.get());

    //add_cylinder({
    //    .position = {4.0f, 0.0f, 0.0f},
    //    .sector_count = 16,
    //    .radius = 0.5f,
    //    .height = 2.0f,
    //}, m_mesh_manager.get());

   load_cube({
        .position = {4.0f, -0.5f, 5.0f},
        .size = {1.0f, 1.0f, 1.0f},
        .rotation = {0.0f, 45.0f, 0.0f},
        .material = box_material,
        .shininess = 32.0f,
    }, m_mesh_manager.get());

    load_cube({
        .position = {2.0f, -0.25f, 4.5f},
        .size = {1.5f, 1.5f, 1.5f},
        .rotation = {0.0f, -45.0f, 0.0f},
        .material = box_material,
        .shininess = 32.0f,
    }, m_mesh_manager.get());

    load_model({
        .position = {6.0f, -1.0f, 3.0f},
        .size = {0.2f, 0.2f, 0.2f},
        .rotation = {0.0f, 180.0f, 0.0f},
        .file_path = "../resources/latern/Lantern.gltf",
    }, m_mesh_manager.get());

    load_model({
        .position = {1.0f, -1.0f, 16.0f},
        .size = {2.0f, 2.0f, 2.0f},
        .rotation = {0.0f, 0.0f, 0.0f},
        .material = house_material,
        .file_path = "../resources/cottage/cottage.obj",
    }, m_mesh_manager.get());

    load_plane({
        .position = {0.0f, -1.0f, 0.0f},
        .size = {10.0f, 200.0f},
        .rotation = {0.0f, 0.0f, 0.0f},
        .material = road_material,
        .tile_count_x = 4.0f,
        .tile_count_y = 100.0f,
    }, m_mesh_manager.get());

    load_plane({
        .position = {-10.0f, -1.0f, 0.0f},
        .size = {10.0f, 200.0f},
        .rotation = {0.0f, 0.0f, 0.0f},
    }, m_mesh_manager.get());

    load_plane({
        .position = {10.0f, -1.0f, 0.0f},
        .size = {10.0f, 200.0f},
        .rotation = {0.0f, 0.0f, 0.0f},
    }, m_mesh_manager.get());

    set_directional_light({
        .direction = {-0.0f, -10.0f, -8.0f},
        .ambient = {0.0f, 0.0f, 0.0f},
        .diffuse = {0.2f, 0.2f, 0.2f},
        .specular = {0.1f, 0.1f, 0.1f},
    });

    add_point_light({
        .position = {0.0f, 2.0f, 3.0f},
        .constant = 1.0f,
        .linear = 0.02f,
        .quadratic = 0.09f,
        .ambient = { 0.4f, 0.4f, 0.4f },
        .diffuse = { 0.7f, 0.7f, 0.7f },
        .specular = { 1.0f, 1.0f, 1.0f },
    });

    shader.use();
    shader.set_mat4("projection", m_proj_matrix);
    shader.set_mat4("view", m_view_matrix);

    shader.set_vec3("view_pos", {0.0f, 2.0f, 20.0f});

    DirectionalLight dir_light = m_light_manager->get_directional_light();
    shader.set_vec3("directional_light.direction", dir_light.direction);
    shader.set_vec3("directional_light.ambient", dir_light.ambient);
    shader.set_vec3("directional_light.diffuse", dir_light.diffuse);
    shader.set_vec3("directional_light.specular", dir_light.specular);

    std::vector<PointLight> point_lights = m_light_manager->get_point_lights();
    shader.set_int("num_point_lights", (GLint)point_lights.size());

    for (int i = 0; i < point_lights.size(); i++) {
        shader.set_vec3("point_lights[" + std::to_string(i) + "].position", point_lights[i].position);
        shader.set_float("point_lights[" + std::to_string(i) + "].constant", (GLfloat)point_lights[i].constant);
        shader.set_float("point_lights[" + std::to_string(i) + "].linear", (GLfloat)point_lights[i].linear);
        shader.set_float("point_lights[" + std::to_string(i) + "].quadratic", (GLfloat)point_lights[i].quadratic);
        shader.set_vec3("point_lights[" + std::to_string(i) + "].ambient", point_lights[i].ambient);
        shader.set_vec3("point_lights[" + std::to_string(i) + "].diffuse", point_lights[i].diffuse);
        shader.set_vec3("point_lights[" + std::to_string(i) + "].specular", point_lights[i].specular);
    }

    double previous_time = glfwGetTime();
    int frame_count = 0;

    while (!glfwWindowShouldClose(m_window->get_handle()))
    {
        double current_time = glfwGetTime();
        frame_count++;

        if (current_time - previous_time >= 1.0) {
            std::cout << "FPS: " << frame_count << "\n";

            frame_count = 0;
            previous_time = current_time;
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (const auto& mesh : m_mesh_manager->get_meshes()) {
            renderer.draw(*mesh.second);
        }


        glfwSwapBuffers(m_window->get_handle());
        glfwPollEvents();
    }
}
}
