#include "boson/managers/light_manager.h"

namespace boson {

LightManager::LightManager() {
    m_point_lights.reserve(m_max_point_lights);
}

LightManager::~LightManager() {
}

void LightManager::set_directional_light(const DirectionalLight& light) {
    m_directional_light = light;
}

void LightManager::add_point_light(const PointLight& light) {
    if (m_point_lights.size() >= m_max_point_lights) return;

    m_point_lights.emplace_back(light);
}

}
