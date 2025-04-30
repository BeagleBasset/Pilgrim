#include <iostream>
#include "States/GameStates/PausedGameState.hpp"
#include "Game.hpp"

//--------------------------------------
// PausedGameState - Member Functions
//--------------------------------------

void PausedGameState::Update(float dt, Renderer& renderer) {
	// Update menu logic here
}

void PausedGameState::Render(Renderer& renderer) {
	// Render menu graphics here
}

void PausedGameState::HandleInput(Renderer& renderer) {
	// Handle menu input here
	GLFWwindow* window = renderer.GetWindow().get();
	bool pPressed = glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS;
	

	// Csak akkor vált állapotot, ha most lenyomva van, de elõzõ frame-ben nem volt
	if (pPressed && !Game::GetInstance().pPressedLastFrame) {
		Game::GetInstance().ChangeState(GAME_STATE_PLAYING);
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || renderer.WindowShouldClose()) {
		Game::GetInstance().Quit();
	}

	Game::GetInstance().pPressedLastFrame = pPressed;
}

void PausedGameState::Enter(Renderer& renderer) {
	// Code to execute when entering the menu state
	std::cout << "Entering PausedGameState..." << std::endl;
}

void PausedGameState::Exit() {
	// Code to execute when exiting the menu state
	std::cout << "Exiting PausedGameState..." << std::endl;
}