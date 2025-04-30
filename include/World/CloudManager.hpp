#pragma once

//--------------------------------------
//✝JMJ✝
//
// CloudManager Class
//
// DESCRIPTION:
//
// This class is responsible for managing the cloud rendering in the game.
//
// DATE: 2025-04-30
//
//---------------------------------------

#include <vector>
#include <random>
#include <glm/glm.hpp>

struct Cloud {
    glm::vec3 pos;
    float scale;
};

class CloudManager {
public:
    void GenerateClouds(int count, float radius, float baseHeight);
    void Update(const glm::vec3& cameraPos);
	std::vector<Cloud>& GetClouds() { return m_clouds; }
private:
    std::vector<Cloud> m_clouds;
    int     m_count = 0;
    float   m_radius = 0.0f;
    float   m_baseHeight = 0.0f;

    // Random engine and distributions
    std::mt19937 m_rng;
    std::uniform_real_distribution<float> m_distAngle;
    std::uniform_real_distribution<float> m_distRadius;
    std::uniform_real_distribution<float> m_distScale;
};