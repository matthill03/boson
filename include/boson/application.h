#pragma once
#include <GL/glew.h>
#include <unordered_map>
#include <memory>
#include <vector>

#include "boson/window.h"
#include "boson/shader.h"
#include "boson/renderer.h"
#include "boson/object.h"
#include "boson/managers/mesh_manager.h"

namespace boson {
class Application {
public:
    Application(const WindowConfig_t& window_config);
    ~Application();

    void run();
    void add_cube(const CubeInfo& info);
    void add_plane(const PlaneInfo& info);
    void add_sphere(const SphereInfo& info);
    void add_cylinder(const CylinderInfo& info);

private:
    std::unique_ptr<Window> m_window = nullptr;
    std::unique_ptr<MeshManager> m_mesh_manager = std::make_unique<MeshManager>();

    // Object data per vao
    std::unordered_map<std::string, std::vector<Object>> m_obj_data = {};

    glm::mat4 m_proj_matrix = {};
    glm::mat4 m_view_matrix = {};

};
}
