#pragma once

//--------------------------------------
//✝JMJ✝
//
// Terrain Class
//
// DESCRIPTION:
//
// This class represents the terrain in the game world.
// It handles the generation of the terrain, including height maps and textures.
//
// DATE: 2025-04-29
//
//---------------------------------------

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct TerrainMesh {
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
};

