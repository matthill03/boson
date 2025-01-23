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

void Application::add_model(const ModelInfo& info) {
    std::shared_ptr<Mesh> mesh = m_mesh_manager->get_mesh(info.file_path);

    if (mesh == nullptr) {
        std::shared_ptr<Mesh> new_mesh = m_mesh_manager->load_model_mesh(info.file_path);

        Object new_obj = Object({info.position, info.size, info.rotation, info.material.value_or(Material())});
        if (!info.material.has_value() && new_mesh->has_file_textures()) {
            new_mesh->push_instance_gpu(new_obj.get_model(), 0);
            return;
        }

        new_mesh->push_instance({new_obj.get_model(), info.material.value_or(Material())});

        return;
    }
    Object new_obj = Object({info.position, info.size, info.rotation, info.material.value_or(Material())});
    mesh->push_instance({new_obj.get_model(), info.material.value_or(Material())});

}

void Application::add_cube(const CubeInfo& info) {
    std::shared_ptr<Mesh> mesh = m_mesh_manager->get_mesh("cube");

    if (mesh == nullptr) {
        // Item does not exists
        std::shared_ptr<Mesh> new_mesh = m_mesh_manager->load_cube_mesh();;

        Object new_obj = Object({info.position, info.size, info.rotation, info.material.value_or(Material())});
        new_mesh->push_instance({new_obj.get_model(), info.material.value_or(Material())});

        return;
    }

    Object new_obj = Object({info.position, info.size, info.rotation, info.material.value_or(Material())});
    mesh->push_instance({new_obj.get_model(), info.material.value_or(Material())});
}

void Application::add_plane(const PlaneInfo& info) {
    std::string plane_name = "plane_" + std::to_string(info.tile_count_x.value_or(1.0f)) + "_" + std::to_string(info.tile_count_y.value_or(1.0f));

    std::shared_ptr<Mesh> mesh = m_mesh_manager->get_mesh(plane_name);

    if (mesh == nullptr) {
        // Item does not exists
        std::shared_ptr<Mesh> new_mesh = m_mesh_manager->load_plane_mesh(info.tile_count_x.value_or(1.0f), info.tile_count_y.value_or(1.0f), plane_name);

        Object new_obj = Object({info.position, glm::vec3(info.size.x, 1.0f, info.size.y), info.rotation, Material()});
        new_mesh->push_instance({new_obj.get_model(), info.material.value_or(Material())});
        //m_obj_data.insert({new_mesh, { Object({info.position, glm::vec3(info.size.x, 1.0f, info.size.y), info.rotation, info.material}) }});
        return;
    }

    Object new_obj = Object({info.position, glm::vec3(info.size.x, 1.0f, info.size.y), info.rotation, Material()});
    mesh->push_instance({new_obj.get_model(), info.material.value_or(Material())});
}

void Application::add_sphere(const SphereInfo& info) {
    std::string sphere_name = "sphere_" + std::to_string(info.sector_count) + "_" + std::to_string(info.stack_count) + "_" + std::to_string(static_cast<GLint>(info.radius));

    std::shared_ptr<Mesh> mesh = m_mesh_manager->get_mesh(sphere_name);

    if (mesh == nullptr) {
        // Item does not exists
        std::shared_ptr<Mesh> new_mesh = m_mesh_manager->load_sphere_mesh(info.sector_count, info.stack_count, info.radius, sphere_name);

        Object new_obj = Object({info.position, glm::vec3(1.0f), info.rotation, info.material});
        new_mesh->push_instance({new_obj.get_model(), Material()});
        //m_obj_data.insert({new_mesh, { Object({info.position, glm::vec3(1.0f), info.rotation, info.material}) }});
        return;
    }

    m_obj_data.at(sphere_name).push_back(Object({info.position, glm::vec3(1.0f), info.rotation, info.material}));

}

void Application::add_cylinder(const CylinderInfo& info) {
    std::string cylinder_name = "cylinder_" + std::to_string(info.sector_count) + "_" + std::to_string(static_cast<GLint>(info.radius)) + "_" + std::to_string(static_cast<GLint>(info.height));

    std::shared_ptr<Mesh> mesh = m_mesh_manager->get_mesh(cylinder_name);

    if (mesh == nullptr) {
        // Item does not exists
        std::shared_ptr<Mesh> new_mesh = m_mesh_manager->load_cylinder_mesh(info.sector_count, info.radius, info.height, cylinder_name);

        Object new_obj = Object({info.position, glm::vec3(1.0f), info.rotation, info.material});
        new_mesh->push_instance({new_obj.get_model(), Material()});
        //m_obj_data.insert({new_mesh, { Object({info.position, glm::vec3(1.0f), info.rotation, info.material}) }});
        return;
    }

    m_obj_data.at(cylinder_name).push_back(Object({info.position, glm::vec3(1.0f), info.rotation, info.material}));
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

    Texture road_diffuse("../resources/asphalt.png", TextureType::DIFFUSE);
    std::vector<Texture> road_texture = { road_diffuse };

    Material box_material = {
        .texture_maps = textures,
    };

    Material house_material = {
        .texture_maps = house_texture,
    };

    Material road_material = {
        .texture_maps = road_texture,
    };


    /*add_sphere({*/
    /*    .position = {},*/
    /*    .sector_count = 32,*/
    /*    .stack_count = 16,*/
    /*    .radius = 1,*/
    /*    .textures = textures_two*/
    /*});*/

    /*add_cylinder({*/
    /*    .position = {},*/
    /*    .sector_count = 16,*/
    /*    .radius = 0.5f,*/
    /*    .height = 2.0f,*/
    /*    .textures = textures_two,*/
    /*});*/

    add_cube({
        .position = {4.0f, -0.5f, 5.0f},
        .size = {1.0f, 1.0f, 1.0f},
        .rotation = {0.0f, 45.0f, 0.0f},
        .material = box_material,
        .shininess = 32.0f,
    });

    add_cube({
        .position = {2.0f, -0.25f, 4.5f},
        .size = {1.5f, 1.5f, 1.5f},
        .rotation = {0.0f, -45.0f, 0.0f},
        .material = box_material,
        .shininess = 32.0f,
    });

    add_model({
        .position = {6.0f, -1.0f, 3.0f},
        .size = {0.2f, 0.2f, 0.2f},
        .rotation = {0.0f, 180.0f, 0.0f},
        .file_path = "../resources/latern/Lantern.gltf",
    });

    add_model({
        .position = {1.0f, -1.0f, 16.0f},
        .size = {2.0f, 2.0f, 2.0f},
        .rotation = {0.0f, 0.0f, 0.0f},
        .material = house_material,
        .file_path = "../resources/cottage/cottage.obj",
    });

    add_plane({
        .position = {0.0f, -1.0f, 0.0f},
        .size = {10.0f, 200.0f},
        .rotation = {0.0f, 0.0f, 0.0f},
        .material = road_material,
        .tile_count_y = 8.0f
        //.textures = textures_two,
    });

    add_plane({
        .position = {-10.0f, -1.0f, 0.0f},
        .size = {10.0f, 200.0f},
        .rotation = {0.0f, 0.0f, 0.0f},
        //.textures = textures_two,
    });

    add_plane({
        .position = {10.0f, -1.0f, 0.0f},
        .size = {10.0f, 200.0f},
        .rotation = {0.0f, 0.0f, 0.0f},
        //.textures = textures_two,
    });

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
