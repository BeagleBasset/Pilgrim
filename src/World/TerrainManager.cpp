#include "World/TerrainManager.hpp"
#include <cmath>
#include <sstream>

TerrainManager::TerrainManager(int chunkSize, int renderDistance)
    : m_chunkSize(chunkSize), m_renderDistance(renderDistance) {}

void TerrainManager::Update(const glm::vec3& cameraPos)
{
    m_visibleChunks.clear();

    int camChunkX = static_cast<int>(std::floor(cameraPos.x / m_chunkSize));
    int camChunkZ = static_cast<int>(std::floor(cameraPos.z / m_chunkSize));

    for (int dx = -m_renderDistance; dx <= m_renderDistance; ++dx) {
        for (int dz = -m_renderDistance; dz <= m_renderDistance; ++dz) {
            int chunkX = camChunkX + dx;
            int chunkZ = camChunkZ + dz;

            std::string key = MakeKey(chunkX, chunkZ);

            if (m_chunks.find(key) == m_chunks.end()) {
                m_chunks[key] = TerrainChunk(chunkX, chunkZ, m_chunkSize);
            }

            bool alreadyAdded = false;
            for (const auto& chunk : m_visibleChunks) {
                auto chunkCoord = chunk->GetChunkCoord();
                int x = chunkCoord[0];
                int z = chunkCoord[1];
                if (x == chunkX && z == chunkZ) {
                    alreadyAdded = true;
                    break;
                }
            }

            if (!alreadyAdded) {
                m_visibleChunks.push_back(&m_chunks.at(key));
            }
        }
    }
}

const std::vector<TerrainChunk*>& TerrainManager::GetVisibleChunks() const {
    return m_visibleChunks;
}

std::string TerrainManager::MakeKey(int x, int z) const {
    return std::to_string(x) + "_" + std::to_string(z);
}