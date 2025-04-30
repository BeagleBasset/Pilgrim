#pragma once

//--------------------------------------
//✝JMJ✝
//
// Renderer Class
//
// DESCRIPTION:
//
// This class is responsible for rendering the game world and its components.
// It handles the graphics context, rendering pipeline, and any necessary shaders.
// Using OpenGL.
//
//	
// DATE: 2025-04-29
//
//---------------------------------------

#include "World/Terrain.hpp"
#include "World/CloudManager.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtc/type_ptr.hpp> 
#include <string>
#include <memory>
#include <iostream>
#include <utility>

class Renderer {
	public:
		Renderer() = default;
		~Renderer();
		bool Init(int width, int height, const std::string& title);
		void BeginFrame();
		void EndFrame();
		bool WindowShouldClose();
		std::shared_ptr<GLFWwindow> GetWindow() const;
		std::pair<int, int> GetWindowSize() const;
		void Setup2D();
		void Setup3D();
		void ProcessMouseMovement(double xpos, double ypos);
		void DrawMesh(const TerrainMesh& mesh, const glm::mat4& model);
		void DrawClouds(const std::vector<Cloud>& clouds);
		void InitCloud();
		static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

		glm::vec3 GetCameraPos() const { return m_cameraPos; }
		glm::vec3 GetCameraFront() const { return m_cameraFront; }
		glm::vec3 GetCameraUp() const { return m_cameraUp; }

		void SetCameraPos(const glm::vec3& pos) { m_cameraPos = pos; }
		void SetCameraFront(const glm::vec3& front) { m_cameraFront = front; }
		void SetCameraUp(const glm::vec3& up) { m_cameraUp = up; }

		glm::mat4 GetProjectionMatrix() const;
		glm::mat4 GetViewMatrix() const;

	private:
		void UploadMeshData(const TerrainMesh& mesh);
		int m_width, m_height;
		std::shared_ptr<GLFWwindow> m_window;
		float m_yaw = -90.0f;       
		float m_pitch = 0.0f;       
		float m_lastX = 0.0f;       
		float m_lastY = 0.0f;       
		bool m_firstMouse = true;   
		glm::vec3 m_cameraPos = { 0.0f, 5.0f, 10.0f };
		glm::vec3 m_cameraFront = { 0.0f, 0.0f, -1.0f };
		glm::vec3 m_cameraUp = { 0.0f, 1.0f, 0.0f };
		GLuint terrainShaderProgram;
		GLuint terrainVAO;
		GLuint terrainVBO;
		GLuint terrainEBO;
		GLuint cloudShaderProgram;
		GLuint cloudVAO;
		GLuint cloudVBO;
		int indexCount;
		
};
