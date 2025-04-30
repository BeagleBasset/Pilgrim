#include <iostream>
#include "States/GameStates/PlayingGameState.hpp"
#include "Game.hpp"
//--------------------------------------
// PlayingGameState - Member Functions
//--------------------------------------

void PlayingGameState::Update(float dt, Renderer& renderer) {
	// Update menu logic here
	m_terrainManager.Update(renderer.GetCameraPos());
	m_cloudManager.Update(renderer.GetCameraPos());

}

void PlayingGameState::Render(Renderer& renderer) {
	
	renderer.Setup3D();
	renderer.DrawClouds(m_cloudManager.GetClouds());

	for (const TerrainChunk* chunk : m_terrainManager.GetVisibleChunks()) {
		TerrainMesh mesh = chunk->GenerateMesh();  // pointer -> használj ->
		auto chunkCoord = chunk->GetChunkCoord();
		int x = chunkCoord[0];
		int z = chunkCoord[1];

		glm::vec3 chunkPos = glm::vec3(x * chunkSize, -64.0f, z * chunkSize);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), chunkPos);
		renderer.DrawMesh(mesh, model); 
	}

}

void PlayingGameState::HandleInput(Renderer& renderer) {
	GLFWwindow* window = renderer.GetWindow().get();
	float dt = Game::GetInstance().GetDeltaTime();
	float velocity = m_moveSpeed * dt;

	glm::vec3 pos = renderer.GetCameraPos();
	glm::vec3 front = glm::normalize(renderer.GetCameraFront());
	glm::vec3 up = renderer.GetCameraUp();
	glm::vec3 right = glm::normalize(glm::cross(front, up));

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		pos += front * velocity;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		pos -= front * velocity;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		pos -= right * velocity;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		pos += right * velocity;

	renderer.SetCameraPos(pos);

	bool pPressed = glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS;
	static bool pPressedLastFrame = false;

	if (pPressed && !Game::GetInstance().pPressedLastFrame) {
		Game::GetInstance().ChangeState(GAME_STATE_PAUSED);
	}

	Game::GetInstance().pPressedLastFrame = pPressed;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || renderer.WindowShouldClose()) {
		Game::GetInstance().Quit();
	}

}

void PlayingGameState::Enter(Renderer& renderer) {
	// Code to execute when entering the menu state
	std::cout << "Entering PlayingGameState..." << std::endl;

	renderer.Setup3D();
	renderer.InitCloud();
	m_cloudManager.GenerateClouds(10,80,40);
}

void PlayingGameState::Exit() {
	// Code to execute when exiting the menu state
	std::cout << "Exiting PlayingGameState..." << std::endl;
}