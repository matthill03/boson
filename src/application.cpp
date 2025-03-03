#include "boson/application.h"

namespace boson {

Application::Application(const std::string& file_path) {
    if (m_scene == nullptr) {
        m_scene = std::make_unique<Scene>(file_path);
    }
}

Application::~Application() {
}

void Application::run() {
    m_scene->run();

    // TODO: Make sure the scene can load spheres and cylinders...
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
}
}
