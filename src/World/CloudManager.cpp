#include "World/CloudManager.hpp"
#include <glm/gtc/constants.hpp>
#include <cmath>

void CloudManager::GenerateClouds(int count, float radius, float baseHeight) {
    m_count = count;
    m_radius = radius;
    m_baseHeight = baseHeight;

    // RNG init
    std::random_device rd;
    m_rng = std::mt19937(rd());
    m_distAngle = std::uniform_real_distribution<float>(0.0f, glm::two_pi<float>());
    m_distRadius = std::uniform_real_distribution<float>(0.0f, radius);
    m_distScale = std::uniform_real_distribution<float>(10.0f, 30.0f);

    m_clouds.clear();
    m_clouds.reserve(m_count);

    // Initial positions around origin (0, baseHeight, 0)
    for (int i = 0; i < m_count; ++i) {
        float angle = m_distAngle(m_rng);
        float r = m_distRadius(m_rng);
        float x = std::cos(angle) * r;
        float z = std::sin(angle) * r;
        float s = m_distScale(m_rng);
        m_clouds.push_back({ glm::vec3(x, m_baseHeight, z), s });
    }
}

void CloudManager::Update(const glm::vec3& cameraPos) {
    for (auto& cloud : m_clouds) {
        glm::vec3 rel = cloud.pos - cameraPos;
        float dist = std::sqrt(rel.x * rel.x + rel.z * rel.z);
        if (dist > m_radius) {
            float angle = m_distAngle(m_rng);
            float r = m_distRadius(m_rng);
            float x = cameraPos.x + std::cos(angle) * r;
            float z = cameraPos.z + std::sin(angle) * r;
            float s = m_distScale(m_rng);
            cloud.pos = glm::vec3(x, m_baseHeight, z);
            cloud.scale = s;
        }
    }
}