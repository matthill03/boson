#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "boson/managers/mesh_manager.h"
#include "boson/managers/light_manager.h"
#include "boson/managers/object_manager.h"

#include "boson/window.h"
#include "boson/shader.h"
#include "boson/renderer.h"
#include "boson/mesh.h"
#include "boson/cubemap.h"

#include <iostream>
#include <fstream>
#include <string>

namespace boson {

    class Scene {

    public:
        Scene(const std::string& file_path);
        ~Scene();

        void run();

    private:

        void load_scene(const std::string& file_path);

        std::string m_file_path;

        glm::mat4 m_proj_matrix = {};
        glm::mat4 m_view_matrix = {};

        std::unique_ptr<Window> m_window = nullptr;
        std::unique_ptr<MeshManager> m_mesh_manager = std::make_unique<MeshManager>();
        std::unique_ptr<LightManager> m_light_manager = std::make_unique<LightManager>();

        std::shared_ptr<Shader> m_shader = nullptr;
        std::shared_ptr<Renderer> m_renderer = nullptr;

        std::shared_ptr<Skybox> m_skybox = nullptr;

        std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures = {};
        std::unordered_map<std::string, std::vector<std::shared_ptr<Texture>>> m_texture_sets = {};

        std::unordered_map<std::string, std::shared_ptr<Material>> m_materials = {};


    };

}
