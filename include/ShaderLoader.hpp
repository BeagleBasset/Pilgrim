#pragma once

//--------------------------------------
//✝JMJ✝
//
// ShaderLoader Function
//
// DESCRIPTION:
//
// This function loads a shader from a file, compiles it, and checks for errors.
// It returns the shader ID if successful, or 0 if there was an error.
// It is used to load vertex and fragment shaders for the game.
//
// DATE: 2025-04-29
//
//---------------------------------------

#include <glad/glad.h>

GLuint LoadShaders(const char* vertex_path, const char* fragment_path);