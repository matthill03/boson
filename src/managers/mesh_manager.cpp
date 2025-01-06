#include "boson/managers/mesh_manager.h"
#include "assimp/matrix4x4.h"

namespace boson {

MeshManager::MeshManager() {

}

MeshManager::~MeshManager() {
}

std::shared_ptr<Mesh> MeshManager::process_scene_mesh(const aiNode& child, const aiScene& scene, const std::string& model_root_path) {
    std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>(child.mName.C_Str(), m_next_mesh_id);
    m_next_mesh_id++;

    aiMesh* mesh = scene.mMeshes[child.mMeshes[0]];
    aiMatrix4x4 base_transform = child.mTransformation;

    new_mesh->set_base_tranform(convert_matrix(base_transform));

    for (GLuint i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

        if (mesh->HasNormals()) {
            vertex.normal = glm::vec3((GLfloat)mesh->mNormals[i].x, (GLfloat)mesh->mNormals[i].y, (GLfloat)mesh->mNormals[i].z);
        } else {
            vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        if (mesh->HasTextureCoords(0)) {
            vertex.tex_coord = glm::vec2((GLfloat)mesh->mTextureCoords[0][i].x, (GLfloat)mesh->mTextureCoords[0][i].y);
        } else {
            vertex.tex_coord = glm::vec2(0.0f, 0.0f);
        }

        new_mesh->push_vertex(vertex);

    }

    for (GLuint i = 0; i < mesh->mNumFaces; i++) {
        aiFace& face = mesh->mFaces[i];

        for (GLuint j = 0; j < face.mNumIndices; j++) {
            new_mesh->push_index(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene.mMaterials[mesh->mMaterialIndex];

        aiString diffuse_path;
        aiString specular_path;

        if (material->GetTextureCount(aiTextureType::aiTextureType_DIFFUSE) > 0) {
            material->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0, &diffuse_path);

            new_mesh->add_texture(model_root_path.c_str() + std::string(diffuse_path.C_Str()), TextureType::DIFFUSE);

        }

        if (material->GetTextureCount(aiTextureType::aiTextureType_SPECULAR) > 0) {
            material->GetTexture(aiTextureType::aiTextureType_SPECULAR, 0, &specular_path);

            new_mesh->add_texture(model_root_path.c_str() + std::string(specular_path.C_Str()), TextureType::SPECULAR);
        }

        GLfloat shininess;
        if (material->Get(AI_MATKEY_SHININESS_STRENGTH, shininess) == AI_SUCCESS) {
            new_mesh->set_shininess(shininess);
        }
    }


    new_mesh->send_data();
    return new_mesh;
}

std::shared_ptr<Mesh> MeshManager::load_model_mesh(const std::string& file_path) {
    std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>(file_path, m_next_mesh_id);
    m_next_mesh_id++;

    std::filesystem::path model_root_path(file_path);
    model_root_path.remove_filename();

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(file_path.c_str(), aiProcess_Triangulate);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR >> " << importer.GetErrorString() << "\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "INFO >> Loaded model '" << file_path << "' correctly...\n";

    aiNode* root_node = scene->mRootNode;

    for (int i = 0; i < root_node->mNumChildren; i++) {
        aiNode* child = root_node->mChildren[i];

        std::shared_ptr<Mesh> child_mesh = process_scene_mesh(*child, *scene, model_root_path);

        new_mesh->add_child(child_mesh);
    }

    m_mesh_map.insert({ file_path, new_mesh });
    return new_mesh;
}

std::string MeshManager::load_cube_mesh() {
    std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>("cube", cube_vertices, cube_indices, m_next_mesh_id);
    m_next_mesh_id++;

    m_mesh_map.insert({ "cube", new_mesh});

    return "cube";
}

std::string MeshManager::load_plane_mesh() {
    std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>("plane", plane_vertices, plane_indicies, m_next_mesh_id);
    m_next_mesh_id++;

    m_mesh_map.insert({ "plane", new_mesh});

    return "plane";
}

std::string MeshManager::load_sphere_mesh(GLint sector_count, GLint stack_count, GLfloat radius, const std::string& name) {
    // NOTE: Look at using Cube sphere or ico sphere!!!
    //std::cout << "Sectors: " << sector_count << ", Stacks: " << stack_count << "\n";
    std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>(name, m_next_mesh_id);
    m_next_mesh_id++;

    float xy, x, y, z;
    float nx, ny, nz;
    float s, t;

    const float PI = glm::pi<float>();

    for (int i = 0; i <= stack_count; i++) {
        Vertex vertex;
        float stack_angle = PI / 2 - i * (PI / stack_count);
        xy = radius * glm::cos(stack_angle);
        z = radius * glm::sin(stack_angle);

        for (int j = 0; j <= sector_count; j++) {
            float sector_angle = j * (2 * PI / sector_count);

            // Vertex Position
            x = xy * glm::cos(sector_angle);
            y = xy * glm::sin(sector_angle);


            // Normals
            nx = x / radius;
            ny = y / radius;
            nz = z / radius;

            // Texture Coords
            s = (float)j / sector_count;
            t = (float)i / stack_count;

            new_mesh->push_vertex({glm::vec3(x, y, z), glm::vec3(nx, ny, nz), glm::vec2(s, t)});
        }
    }

    GLuint k1, k2;

    for (int i = 0; i < stack_count; i++) {
        int top = i * (sector_count + 1);
        int bottom = (i + 1) * (sector_count + 1);

        for (int j = 0; j < sector_count; j++) {
            new_mesh->push_index(top + j);
            new_mesh->push_index(bottom + j);
            new_mesh->push_index(top + j + 1);

            new_mesh->push_index(top + j + 1);
            new_mesh->push_index(bottom + j);
            new_mesh->push_index(bottom + j + 1);

        }
    }
    new_mesh->send_data();
    m_mesh_map.insert({ name, new_mesh });

    return name;
}

std::string MeshManager::load_cylinder_mesh(GLint sector_count, GLfloat radius, GLfloat height, const std::string& name) {

    std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>(name, m_next_mesh_id);
    m_next_mesh_id++;

        const float PI = glm::pi<float>();
    float sector_step = 2 * PI / sector_count;
    float sector_angle;

    for (int i = 0; i < 2; i++) {
        float y = (i == 0) ? -0.5f : 0.5f;
        glm::vec3 normal = (i == 0) ? glm::vec3(0.0f, -1.0f, 0.0f) : glm::vec3(0.0f, 1.0f, 0.0f);

        new_mesh->push_vertex({glm::vec3(0.0f, y, 0.0f), normal, glm::vec2(0.5f, 0.5f)});
        GLuint center_index = new_mesh->get_vertex_count();

        for (int j = 0; j <= sector_count; j++ ) {
            sector_angle = j * sector_step;
            float x = radius * glm::cos(sector_angle);
            float z = radius * glm::sin(sector_angle);

            new_mesh->push_vertex({glm::vec3(x, y, z), normal, glm::vec2((x / radius + 1.0f) * 0.5f, (z / radius + 1.0f) * 0.5f)});

            if (j > 0) {
                if (i == 0) {
                    new_mesh->push_index(center_index);
                    new_mesh->push_index(new_mesh->get_vertex_count() - 2);
                    new_mesh->push_index(new_mesh->get_vertex_count() - 1);
                } else {
                    new_mesh->push_index(center_index);
                    new_mesh->push_index(new_mesh->get_vertex_count() - 2);
                    new_mesh->push_index(new_mesh->get_vertex_count() - 1);
                }
            }
        }
    }

    for (int i = 0; i <= sector_count; i++) {
        float sector_angle = i * sector_step;
        float x = radius * glm::cos(sector_angle);
        float z = radius * glm::sin(sector_angle);

        float s = (float)i / sector_count;

        new_mesh->push_vertex({glm::vec3(x, -0.5, z), glm::normalize(glm::vec3(x, 0.0f, z)), glm::vec2(s, 0.0f)});
        new_mesh->push_vertex({glm::vec3(x,  0.5, z), glm::normalize(glm::vec3(x, 0.0f, z)), glm::vec2(s, 1.0f)});

        if (i > 0) {
            GLuint current = new_mesh->get_vertex_count() - 1;
            GLuint previous = new_mesh->get_vertex_count() - 3;

            // Triangle 1
            new_mesh->push_index(current);
            new_mesh->push_index(previous);
            new_mesh->push_index(previous - 1);

            // Triangle 2
            new_mesh->push_index(current - 1);
            new_mesh->push_index(current);
            new_mesh->push_index(previous - 1);
        }
    }

    new_mesh->send_data();
    m_mesh_map.insert({ name, new_mesh });
    return name;
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

glm::mat4 MeshManager::convert_matrix(const aiMatrix4x4& mat) {
    return {
        mat.a1, mat.b1, mat.c1, mat.d1,
        mat.a2, mat.b2, mat.c2, mat.d2,
        mat.a3, mat.b3, mat.c3, mat.d3,
        mat.a4, mat.b4, mat.c4, mat.d4
    };
}

void MeshManager::clear_meshes() {
}

}
