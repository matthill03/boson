#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>

#include <memory>

#include <boson/vertex_array.h>
#include <boson/texture.h>

namespace boson {

typedef struct Material{
    glm::vec3 ambient = {0.8f, 0.8f, 0.8f};
    glm::vec3 diffuse = {0.6f, 0.6f, 0.6f};
    glm::vec3 specular = {0.2f, 0.2f, 0.2f};

    std::vector<Texture> texture_maps = {};
    GLfloat shininess = 1.0f;
} Material;

typedef struct GPUMaterial {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    GLint diffuse_map;
    GLint specular_map;

    GLfloat shininess;

} GPUMaterial;

typedef struct InstanceInfo {
    glm::mat4 transform;
    Material material;

    //std::vector<Texture> textures;
} InstanceInfo;

class Mesh {
public:
    Mesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLuint next_mesh_id);
    Mesh(const std::string& name, GLuint next_mesh_id);
    ~Mesh();

    void bind_data() const { m_data->bind(); }

    void push_vertex(const Vertex vertex);
    void push_index(const GLuint index);
    void push_instance(const InstanceInfo& instance);
    void push_instance_gpu(glm::mat4 transform, int material_index);

    void send_data();

    void set_shininess(GLfloat value) { m_shininess = value; }
    void set_has_file_textures(bool value) { m_has_file_textures = value; }

    GLuint get_id() const { return m_id; }
    GLuint get_index_count() const { return m_data->index_count(); }
    GLuint get_vertex_count() const { return m_data->vertex_count(); }
    GLuint get_instance_count() const { return m_instance_data.size(); }
    std::string get_name() const { return m_name; }

    std::vector<Texture> get_textures() const { return m_textures; }
    std::vector<GPUMaterial> get_materials() const { return m_materials; }
    GLfloat get_shininess() const { return m_shininess; }

    std::vector<std::shared_ptr<Mesh>> get_children() const { return m_child_data; }

    bool has_children() const { return m_child_data.size() > 0; }
    bool has_file_textures() const { return m_has_file_textures; }

    void add_texture(const std::string& file_path, TextureType type);
    void add_material(const GPUMaterial& material);
    void add_child(std::shared_ptr<Mesh> child) { m_child_data.push_back(child); };

private:
    const GLuint m_max_data_size = 1000;
    const GLuint m_max_textures = 64;
    const GLuint m_max_materials = 64;

    bool m_has_file_textures = false;

    GLuint m_id;
    std::string m_name;
    std::unique_ptr<VertexArray> m_data = nullptr;
    std::vector<std::shared_ptr<Mesh>> m_child_data = {};

    std::vector<InstanceData> m_instance_data = {};

    std::vector<Texture> m_textures = {};
    std::vector<GPUMaterial> m_materials = {};

    GLuint diffuse_textures;
    GLuint specular_textures;

    GLfloat m_shininess = 1.0f;

    void create_texture_arrays();
    void process_instance_material(const InstanceInfo& info);
};

}
