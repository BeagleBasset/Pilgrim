#pragma once

//--------------------------------------
//✝JMJ✝
//
// TerrainManager Class
//
// DESCRIPTION:
//
// This class is responsible for managing the terrain chunks in the game world.
// It handles the loading and unloading of chunks based on the camera position.
//
// DATE: 2025-04-30
//
//---------------------------------------

#include <unordered_map>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "World/TerrainChunk.hpp"

class TerrainManager {
public:
    TerrainManager(int chunkSize, int renderDistance);
    void Update(const glm::vec3& cameraPos);
    const std::vector<TerrainChunk*>& GetVisibleChunks() const;

private:
    int m_chunkSize;
    int m_renderDistance;
    std::vector<TerrainChunk*> m_visibleChunks;
    std::unordered_map<std::string, TerrainChunk> m_chunks;
    std::string MakeKey(int x, int z) const;
};