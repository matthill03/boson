#pragma once
#include <glad/gl.h>
#include <unordered_map>
#include <memory>
#include <vector>

#include "boson/window.h"
#include "boson/shader.h"
#include "boson/renderer.h"
#include "boson/managers/mesh_manager.h"
#include "boson/managers/light_manager.h"
#include "boson/managers/object_manager.h"

namespace boson {
class Application {
public:
    Application(const WindowConfig_t& window_config);
    ~Application();

    void run();

    void set_directional_light(const DirectionalLight& light);
    void add_point_light(const PointLight& light);

private:
    std::unique_ptr<Window> m_window = nullptr;
    std::unique_ptr<MeshManager> m_mesh_manager = std::make_unique<MeshManager>();
    std::unique_ptr<LightManager> m_light_manager = std::make_unique<LightManager>();

    glm::mat4 m_proj_matrix = {};
    glm::mat4 m_view_matrix = {};

};
}
