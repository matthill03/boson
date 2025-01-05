#include "boson/managers/mesh_manager.h"

namespace boson {

MeshManager::MeshManager() {

}

MeshManager::~MeshManager() {
}

std::string MeshManager::load_cube_mesh() {
    std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>("cube", square_vertices, square_indices, m_next_mesh_id);
    m_next_mesh_id++;

    m_mesh_map.insert({ "cube", new_mesh});

    return "cube";
}

std::shared_ptr<Mesh> MeshManager::load_model_mesh(const std::string& file_path) {
    return nullptr;
}

std::shared_ptr<Mesh> MeshManager::get_mesh(const std::string& name) {
    auto item = m_mesh_map.find(name);

    if (item == m_mesh_map.end()) {
        return nullptr;
    }

    return item->second;
}

void MeshManager::unload_mesh(const std::string& name) {
}

void MeshManager::clear_meshes() {
}

}
