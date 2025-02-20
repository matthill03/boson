#include "boson/managers/object_manager.h"

namespace boson {

glm::mat4 calculate_transform(glm::vec3 position, glm::vec3 size, glm::vec3 rotation) {
    glm::mat4 model_matrix = glm::mat4(1.0f);

    model_matrix = glm::scale(model_matrix, { size.x, size.y, size.z });

    model_matrix = glm::rotate(model_matrix, glm::radians(rotation.x), { 1.0f, 0.0f, 0.0f });
    model_matrix = glm::rotate(model_matrix, glm::radians(rotation.y), { 0.0f, 1.0f, 0.0f });
    model_matrix = glm::rotate(model_matrix, glm::radians(rotation.z), { 0.0f, 0.0f, 1.0f });

    model_matrix = glm::translate(model_matrix, { -position.x / size.x, position.y / size.y, position.z / -size.z });

    return model_matrix;
}

void load_model(const ModelInfo& info,  MeshManager* mesh_manager) {
    glm::mat4 model_transform = calculate_transform(info.position, info.size, info.rotation);
    std::shared_ptr<Mesh> mesh = mesh_manager->get_mesh(info.file_path);

    if (mesh == nullptr) {
        std::shared_ptr<Mesh> new_mesh = mesh_manager->load_model_mesh(info.file_path);

        
        if (!info.material.has_value() && new_mesh->has_file_textures()) {
            new_mesh->push_instance_gpu(model_transform, 0);
            return;
        }

        new_mesh->push_instance({ model_transform, info.material.value_or(Material()) });

        return;
    }

    mesh->push_instance({ model_transform, info.material.value_or(Material()) });
}

void load_cube(const CubeInfo& info, MeshManager* mesh_manager) {
    glm::mat4 model_transform = calculate_transform(info.position, info.size, info.rotation);
    std::shared_ptr<Mesh> mesh = mesh_manager->get_mesh("cube");

    if (mesh == nullptr) {
        // Item does not exists
        std::shared_ptr<Mesh> new_mesh = mesh_manager->load_cube_mesh();

        new_mesh->push_instance({ model_transform, info.material.value_or(Material()) });

        return;
    }

    mesh->push_instance({ model_transform, info.material.value_or(Material()) });
}

void load_plane(const PlaneInfo& info, MeshManager* mesh_manager) {
    glm::mat4 model_transofrm = calculate_transform(info.position, {info.size.x, 1.0f, info.size.y}, info.rotation);

    std::string plane_name = "plane_" + std::to_string(info.tile_count_x.value_or(1.0f)) + "_" + std::to_string(info.tile_count_y.value_or(1.0f));

    std::shared_ptr<Mesh> mesh = mesh_manager->get_mesh(plane_name);

    if (mesh == nullptr) {
        // Item does not exists
        std::shared_ptr<Mesh> new_mesh = mesh_manager->load_plane_mesh(info.tile_count_x.value_or(1.0f), info.tile_count_y.value_or(1.0f), plane_name);

        new_mesh->push_instance({ model_transofrm, info.material.value_or(Material()) });
        return;
    }

    mesh->push_instance({ model_transofrm, info.material.value_or(Material()) });
}

void load_sphere(const SphereInfo& info, MeshManager* mesh_manager) {
    glm::mat4 model_transform = calculate_transform(info.position, glm::vec3(1.0f), info.rotation);
    std::string sphere_name = "sphere_" + std::to_string(info.sector_count) + "_" + std::to_string(info.stack_count) + "_" + std::to_string(static_cast<GLint>(info.radius));

    std::shared_ptr<Mesh> mesh = mesh_manager->get_mesh(sphere_name);

    if (mesh == nullptr) {
        // Item does not exists
        std::shared_ptr<Mesh> new_mesh = mesh_manager->load_sphere_mesh(info.sector_count, info.stack_count, info.radius, sphere_name);

        new_mesh->push_instance({ model_transform, info.material.value_or(Material())});
        return;
    }

    mesh->push_instance({ model_transform, info.material.value_or(Material()) });
}

void load_cylinder(const CylinderInfo& info, MeshManager* mesh_manager) {
    glm::mat4 model_transform = calculate_transform(info.position, glm::vec3(1.0f), info.rotation);
    std::string cylinder_name = "cylinder_" + std::to_string(info.sector_count) + "_" + std::to_string(static_cast<GLint>(info.radius)) + "_" + std::to_string(static_cast<GLint>(info.height));

    std::shared_ptr<Mesh> mesh = mesh_manager->get_mesh(cylinder_name);

    if (mesh == nullptr) {
        // Item does not exists
        std::shared_ptr<Mesh> new_mesh = mesh_manager->load_cylinder_mesh(info.sector_count, info.radius, info.height, cylinder_name);

        new_mesh->push_instance({ model_transform, info.material.value_or(Material())});
        return;
    }

    mesh->push_instance({ model_transform, info.material.value_or(Material()) });
}

}
