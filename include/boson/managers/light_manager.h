#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>

#include <vector>

namespace boson {

typedef struct DirectionalLight {
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
} DirectionalLight;

typedef struct PointLight {
    glm::vec3 position;

    GLfloat constant;
    GLfloat linear;
    GLfloat quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
} PointLight;

class LightManager {

public:
    LightManager();
    ~LightManager();

    void set_directional_light(const DirectionalLight& light);
    void add_point_light(const PointLight& light);

    DirectionalLight get_directional_light() const { return m_directional_light; }
    std::vector<PointLight> get_point_lights() const { return m_point_lights; }

private:
    const GLuint m_max_point_lights = 4;

    DirectionalLight m_directional_light = {};
    std::vector<PointLight> m_point_lights = {};
};

}
