#include "World/TerrainChunk.hpp"
#include "World/Terrain.hpp"
#include <sol-prog/PerlinNoise.h>

TerrainChunk::TerrainChunk(int x, int z, int size)
    : m_x(x), m_z(z), m_size(size) {}

glm::ivec2 TerrainChunk::GetChunkCoord() const {
    return { m_x, m_z };
}

TerrainMesh TerrainChunk::GenerateMesh() const {
    TerrainMesh mesh;
    PerlinNoise noise(seed);

    for (int i = 0; i <= m_size; ++i) {
        for (int j = 0; j <= m_size; ++j) {
            float localX = static_cast<float>(i);
            float localZ = static_cast<float>(j);

            float worldX = (m_x * m_size) + i;
            float worldZ = (m_z * m_size) + j;

            double elevation = noise.noise(worldX * frequency, worldZ * frequency, 0.0) * amplitude;
            mesh.vertices.emplace_back(localX, elevation, localZ);
        }
    }

    float cutoff = 0.0f; 

    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            int rowLen = m_size + 1;
            int topLeft = i * rowLen + j;
            int topRight = topLeft + 1;
            int bottomLeft = (i + 1) * rowLen + j;
            int bottomRight = bottomLeft + 1;

            const glm::vec3& v0 = mesh.vertices[topLeft];
            const glm::vec3& v1 = mesh.vertices[bottomLeft];
            const glm::vec3& v2 = mesh.vertices[topRight];
            const glm::vec3& v3 = mesh.vertices[bottomRight];

            if (v0.y > cutoff && v1.y > cutoff && v2.y > cutoff) {
                mesh.indices.push_back(topLeft);
                mesh.indices.push_back(bottomLeft);
                mesh.indices.push_back(topRight);
            }

            if (v2.y > cutoff && v1.y > cutoff && v3.y > cutoff) {
                mesh.indices.push_back(topRight);
                mesh.indices.push_back(bottomLeft);
                mesh.indices.push_back(bottomRight);
            }
        }
    }

    return mesh;
}