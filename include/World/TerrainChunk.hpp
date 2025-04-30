#pragma once

//--------------------------------------
//✝JMJ✝
//
// TerrainChunk Class
//
// DESCRIPTION:
//
// This class represents a chunk of terrain in the game world.
// It handles the generation of the terrain mesh, including vertices and indices.
//
// DATE: 2025-04-30
//
//---------------------------------------

#include <glm/glm.hpp>
#include <vector>

struct TerrainMesh;

class TerrainChunk {
public:
    TerrainChunk() = default;
    TerrainChunk(int x, int z, int size);
    TerrainMesh GenerateMesh() const;
    glm::ivec2 GetChunkCoord() const;

private:
    int m_x, m_z;
    int m_size;
    int seed = 12;
	float frequency = 0.01f;
	float amplitude = 150.0f;

};